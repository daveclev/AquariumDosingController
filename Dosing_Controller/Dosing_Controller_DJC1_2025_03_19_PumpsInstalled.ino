
//////////////////////////////////////
//  BOARD SELECTION
//  This sketch is written for a Spark Fun ESP32 WROOM, WRL 15663.
//  Per Spark Fun ESP23 Thing Plus Hookup Guide, select the following board
//  in the Arduino IDE:
//       *** Adafruit ESP32 Feather ***   NOT: "Adafruit Feather ESP32 xxx" !!!
///////////////////////////////////////
//  To allow IDE connection to the ESP32 board, sometime during the compiling process 
//  depress the "0" pushbutton, not the "RESET" pushbutton, on the ESP32 board; release
//  the pushbutton when the word "Connecting..." appears in the Output window.
//////////////////////////////////////// 
//  March 14, 2025 - This revision expands the stage sequence and pump arrangement to include actions
//  for the raptor tank.
//  This revision also includes provisions for the blue lighted pushbutton which will provide a 
//  confirmation that the dosing cycle was completed. Pushbutton: uxcell Momentary Metal Push Button Switch 12mm Mounting Dia 1NO 3-6V Blue LED Light, Flat Head, 2pcs
/////////////////////////////////////

#include <Wire.h> `
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

#include "Class_IO_Register.h"
#include "stages.h"
#include "EEPROM_512.h"
#include "Class_Pump.h"

#include <RV3129.h> // Requires the "RV-3125_Arduino_Library-master" from GitHub
RV3129 rtc; // Create an instance, called "rtc", of the RV3129 class.

#include <OneWire.h>
#include <DallasTemperature.h>

int ESPled = 13;
int fanOutput = 12; // J9 pin 3
int testOutput = 27;// J9 pin 4, used for software timing tests
int hbTime;

int oldmilli = 0;
int newmilli;

int ss, mm, hh; // used for clock time
int startSec, startMin, startHr;// used for setting the start time for the dose cycle

int days, Weekdays, months, years;

//  Create an instance of the MCP23008 Class for each MCP23008 IO  expander device, pass the I2C address to the instance.
MCP23008 Dosing1(0x24);     // U12 address is 0x24.  A0=0, A1=0, A2=1
MCP23008 Dosing2(0x22);     // U10 address is 0x22.  A0=0, A1=1, A2=0
MCP23008 DiscreteIO(0x20);  // U5  address is 0x20.  A0=0, A1=0, A2=0
MCP23008 SpareIO(0x26);     // U13 address is 0x26.  A0=0, A1=1, A2=1
MCP23008 Relay(0x21);       // U14 address is 0x21.  A0=1, A1=0, A2=0 

// Spare IO U13 usage:
const byte selSwRight = 0; // Input on J12 MCP, connected pin 1 "SPO" black, selector switch, right position
const byte selSwCenter = 1; // Input on J12 MCP, connected to pin 2 "SP1" white, selector switch, center positon
const byte selSwLeft = 2; // Input on J12 MCP, connected to pin 3 "SP2" gray, selector switch, left position
const byte pbLeft = 3; // Input on J12 MCP, connected to pin 4 "SP3" violet, left pushbutton 
const byte pbCenter = 4; // Input on J12 MCP, connected to pin 5 "SP4" blue, center pushbutton
const byte pbRight = 5; // Input on J12 MCP, connected to pin 6 "SP5" green, right pushbutton 

// ESP inputs used for rotary encoder
const byte SWinput = 33;  // Encoder SW pin is connected to J9-pin 5, ESP IO 33
const byte CLKinput = 15; // Encoder CLK pin is connected to J9-pin 6, ESP IO 15
const byte DTinput = 32;  // Encoder DT pin is connected to J9-pin 7, ESP IO 32

// Other variables that will be used with the rotary encoder.
byte SW, DT;
int lastStateCLK, currentStateCLK;
int multip; //This it the multiplier that will be used for fast speed encoder operation when the encoder shaft is depressed.
int encoderCount = 100; // the ISR that handles interrupts from the encoder will increment or decrement this number
int pbDelay = 100;  // This is the debounce delay that will occur whenever the pushbutton GPIO port is read

//  Create an instance of the M24512 EEPROM class.
M24512 DosEEPROM(0x50); // 0x50 is I2C address for accessing the memory in the M24512 device. 0x58 addressed the device's ID page
//byte myData[20];  // This array will be used to pass data between the main program and the EEPROM methods of the EEPROM-512 class.

byte k = 0; // a variable that will be used for various purposes.
byte mode=0, oldMode; // will be used to control introduction as mode switch is moved from one mode to another.

// Create an instance of the "Stage" class for each stage in the sequential control:
// Stage definition: Stage #, Name, Countdown value, EEPROM memory base.
Stage flush1        (1, "Flush 1",    24,  0x0010);
Stage SodaPmp       (2, "SodaAsh",    50, 0x0020);
Stage flush2        (3, "Flush 2",    30, 0x0030);
Stage Part_C        (4, "Part C",     100, 0x0040);
Stage flush3        (5, "Flush 3",    10, 0x0050);
Stage vinegar       (6, "Vinegar",    40, 0x0060);
Stage flush4        (7, "Flush 4",    20, 0x0070);
Stage phyto         (8, "Phyto",      35, 0x0080);
Stage phytoSalt     (9, "Phyto Slt",  70, 0x0090);
Stage flush5        (10, "Flush 5",   10, 0x00A0);
Stage CalcmPmp      (11, "Calcium",   35, 0x00B0);
Stage frshWtr       (12, "Fresh Wtr", 9, 0x00C0);
Stage FinalFlush    (13, "Final Fl",  120, 0x00D0);
Stage Predator_Flush1 (14,"Prdtr Flush1",   20, 0x00E0); // 13+1
Stage Predator_Phyto  (15,"Prdtr Phyto",    70, 0x00F0); // 13+2
Stage Predator_Flush2 (16,"Prdtr Flush2",   35, 0x0100); // 13+3
Stage Predator_Vinegar(17,"Prdtr Vinegr",   35, 0x0110); // 13+4
Stage Predator_Flush3 (18,"Prdtr Flush3",   20, 0x0120); // 13+5
Stage Predator_Spare  (19,"Prdtr Spare",    3, 0x0130); // 13+6
Stage Predator_Flush4 (20,"Prdtr Flush4",   120, 0x0140); // 13+7
Stage wait(10, "delay", 15, 0x0100);

Pump Fresh_WaterPump(0);
Pump SodaPump(1);
Pump PartCPump(2);
Pump CalciumPump(3);
Pump Phyto_BowFrontPump(4); // was names PhytoPpump
Pump Phyto_FertPump(5);
Pump Phyto_SaltPump(6);
Pump Phyto_AirPump(7);
Pump VinegarPump(8);
Pump Phyto_PredatorPump(9);
Pump Flush_BowFrontPump(10); // Was named Flush
Pump Flush_PredatorPump(11);
Pump Vinegar_PredatorPump(12);
Pump Spare_PredatorPump(13);


bool runFlag = false; // used to trigger auto run sequence
byte currentStage;
int currentStageMem = 0x0002; // address in EEEPROM for storing the current stage
int startHrMem = 0x0004;
int startMinMem = 0x0006;
int startSecMem = 0x0008;
bool stageCompleteFlag = false, startStageFlag = true;
byte MtcePage;
bool startMtceFlag;

char maintenanceHeader[] = "Maintenance page: ";
char maintenanceMenu1[] = "Previos Edit    Next";
char maintenanceMenu2[] = "      Cancl    Accpt";
char blankLine[] = "                    ";

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 5
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
// Addresses of DS18B20s
uint8_t sensor1[8] = { 0x28, 0x44, 0x73, 0xE5, 0x0F, 0x00, 0x00, 0x03 };

float tempF;
int tempSetpoint = 70;
int tempSetpointMem = 0x000A;

void setup() {

  Wire.begin();

  sensors.requestTemperatures();

  // These will be used for as heartbeat indicators:
  pinMode(ESPled, OUTPUT);
  pinMode(fanOutput, OUTPUT);
  pinMode(testOutput,OUTPUT);  // Temporary output used for development testing
  
  // Encoder items, based on scheme found at https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/ scroll webpage down to interrupt example.
  pinMode(CLKinput, INPUT_PULLUP);  
  pinMode(DTinput, INPUT_PULLUP);
  pinMode(SWinput, INPUT_PULLUP);  // I added the switch and multiplier feature.
  attachInterrupt(digitalPinToInterrupt(CLKinput), encoderISR, CHANGE); 
	attachInterrupt(digitalPinToInterrupt(DTinput), encoderISR, CHANGE);

  lcd.init();
  lcd.clear();
  lcd.backlight();  // Make sure backlight is on

  oldmilli = millis();

  // Configure registers of some MCP23008 IO expander devices
  Dosing1.MCPWrite(IODIR, 0x00);
  Dosing2.MCPWrite(IODIR, 0x00);
  DiscreteIO.MCPWrite(IODIR, 0xFF);       // Default value is FF (inputs)  but I'm setting just to be sure.
  DiscreteIO.MCPWrite(GPPU, 0x00);        // Default value is 00 (no pullup resistors) but I'm setting just to be sure.
  DiscreteIO.MCPWrite(IPOL, 0b11000000);  // Configure the input polarity so that a depressed switch is seen as a "1"
  SpareIO.MCPWrite(IODIR, 0xFF);          // Configure all IO pins as inputs
  SpareIO.MCPWrite(GPPU,0xFF);            // Enable pullup resistors on all inputs
  SpareIO.MCPWrite(IPOL, 0xFF);           // Set polarity so that a closed switch to ground appears as a "1"  in the GPIO register.
  Relay.MCPWrite(IODIR, 0b11111101);      // Set IO pin 0 as an input(1), IO pin 1 as an output(0) (pin 0 (sw white) and 1 LED (sw orange) used for lighted pushbutton), pins 2 thru 7 as inputs (not used) 
  Relay.MCPWrite(IPOL,  0b00000001);      // Set polartity so that a pushbutton to ground on one of the input pins appears as a "1"  in the GPIO register by setting a 1. 
  Relay.MCPWrite(GPPU,  0b00000001);      // Turn on(1) pull up for pin 0 attached to pushbutton contact (other side of pushbutton contact attached to GND)

  // Uncomment the next line to load a set of values into a new unpopulated EEPROM, i.e.: and new ESP32.
  // initializeEEPROM();  // This procedure is only used to store an initial set of values in an empty EEPROM.
  //DosEEPROM.memWrite(0x0004, startHr); // Initialize hour for start time, startHr, int
  //DosEEPROM.memWrite(0x0006, startMin); // Initialize minutes for start time, startMin, int.
  //DosEEPROM.memWrite(0x0008, startSec); // Initialize minusecodstes for start time, startSec, int.
  //DosEEPROM.memWrite(currentStageMem, currentStage);
  DosEEPROM.memWrite(tempSetpointMem,tempSetpoint);

  retrieveEEPROM(); // Loads stored values from EEPROM.

  lcd.clear();

  rtc.begin();
  rtc.set24Hour();
  
  Relay.PinON(GPIO,1); // Turn ON bit 1 (pushbutton is on bit 0) to energize the LED of the lighted pushbutton connected to bit1 to signal end off dosing cycle.
  
}  // End of setup()


void loop() {

  digitalWrite(testOutput,HIGH);

  //  Heart beat
  hbTime = millis(); 
  digitalWrite(ESPled, bitRead(hbTime, 9));

  sensors.requestTemperatures();
  tempF = sensors.getTempF(sensor1);
  if(tempF>tempSetpoint){digitalWrite(fanOutput, HIGH);}
  else{digitalWrite(fanOutput, LOW);}

  // Read the pushbutton switch (bit 0) and turn off the LED (bit 1) if the pushbutton is pressed (closed).
  byte d = Relay.MCPRead(GPIO);
  if(bitRead(d,0)){                  // Read pin 0 (the first bit) to see if the pushbutton is pressed.
    Relay.PinOFF(GPIO,1);}  // PB LED off: Turn off pin 1 (set second bit to 1 of PinOFF function) because pushbutton is pressed.

  byte k=SpareIO.MCPRead(GPIO); // read the mode selector switch
  delay(02);
  switch(k & 0b00000111){
    case 0b00000100: // Mode Select switch in left "AUTO" position
      mode = 1;
      autoRun();
    break;
    case 0b00000010: // Mode Select switch in center "Maintenance" position
      mode = 2;
      maintenanceMode();
    break;
    case 0b00000001: // Mode Select switch in right "Manaual" position
      mode = 3;
      manualMode();
    break;
    default:
      mode = 0;
      idleMode();
  }  //  End of switch...case structure.

  digitalWrite(testOutput,LOW);
  delay(10);


}  // End of Loop routine.


void encoderISR(){ //based on scheme found at https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/ scroll webpage down to interrupt example.
	currentStateCLK = digitalRead(CLKinput);	// Read the current state of CLK
  SW = digitalRead(SWinput); // I added the switch and multiplier feature.
  if(SW){multip=1;}else{multip=10;}
	// If last and current state of CLK are different, then pulse occurred.
	// React to only 1 state change to avoid double count
	if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
		// If the DT state is different than the CLK state then
		// the encoder is rotating CCW so decrement
		if (digitalRead(DTinput) != currentStateCLK) {
			encoderCount += multip;
		} else {
			// Encoder is rotating CW so increment
			encoderCount -= multip;
		}
	}
	lastStateCLK = currentStateCLK; // Remember last CLK state
}
