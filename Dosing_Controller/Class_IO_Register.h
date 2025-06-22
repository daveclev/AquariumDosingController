
//  Declarations for I2C communication to MCP23008: 
//  const byte Dosing1 = 0x24; // U12 address is 0x24.  A0=0, A1=0, A2=1
//  const byte Dosing2 = 0x22; // U10 address is 0x22.  A0=0, A1=1, A2=0
//  const byte DiscreteIO = 0x20; // U5  address is 0x20.  A0=0, A1=0, A2=0
//  const byte SpareIO = 0x26; // U13 address is 0x26.  A0=0, A1=1, A2=1 unverified
//  const byte Relay = 0x21; // U14 address is 0x21.  A0=1, A1=0, A2=0 unverified

// MCP23008 Register addresses (not register values!):
// Addresses are as shown in Tables 1-2 and 1-3.
// All registers contain 0x00 by default except IODIR is 0xFF.
// Descriptions show what happens if a bit is set to 1.
const byte IODIR = 0x00; // "1" will configure GPIO pin as an input. Default is 0xFF.
const byte IPOL = 0x01; // "1" will cause GPIO register to reflect opposite logic of input pin
const byte GPINTEN = 0x02; // "1" will Enable GPIO input pin for interrupt-on-change event    
const byte DEFVAL = 0x03; // These bits set the compare value for pins configured for interrupt-on-change
const byte INTCON = 0x04; // Controls how the associated pin value is compared for interupt-on-change
const byte IOCON = 0X05; // Various configuration bit
const byte GPPU = 0x06; // "1" will enable pull-up resistor if port pin is configured as an input
const byte INTF = 0x07; // reflects the interrupt condition of any pin that is enabled for interrupts 
const byte INTCAP = 0x08; // captures the GPIO port value at the time an interrupt occurred
const byte GPIO = 0x09; // These bits reflect the logic level on the pins
const byte OLAT = 0x0A; // provides access to the output latches


//////////////////////////////
// CLASS DEFINITION - REGISTER
//////////////////////////////

class MCP23008{ // The MCP23008 class will have only three parameters, listed below.
  public:
    byte MCPaddress; //this is the device I2C address
    
    MCP23008(byte x){ // Constructor for Register class
      MCPaddress = x; // the I2C address for the device
    } // End of Register constructor.

    //  Turn on an output pin.  
    //  Simply sending 0x08 to a register will turn on that bit of a register, but will turn off all other bits. 
    //  To preserve state of other bits we must "OR" existing content of of the register to a mask such as 0b00001000.
    void PinON(byte RegAddress, byte pinNumb){ // mask: for example 0b00001000 sets bit 3
      byte data = MCPRead(RegAddress);  // Read content of specified register
      data = bitSet(data,pinNumb); //  set the desired bit of the register
      MCPWrite(RegAddress, data);
    } // End of PinOn method.

    void PinOFF(byte RegAddress, byte pinNumb){ 
      byte data = MCPRead(RegAddress);  // Read content of specified register
      data = bitClear(data,pinNumb); // Clear the desired bit of the register;
      MCPWrite(RegAddress, data);
    } // End of PinOFF method.

    byte  PinRead(byte RegAddress, byte pinNumb){ // mask: 0b00001000 reads bit 3
      byte data = MCPRead(RegAddress);  // Read content of specified register
      return bitRead(data,pinNumb);
    } // End PinRead method.
    
    void MCPWrite(byte RegAddress, byte value){ // "RegAddress" is the address of the device's register, "value" is what will be written to the register
      Wire.beginTransmission(MCPaddress); // wakes up the MCP23008
      Wire.write(RegAddress); // sets the register pointer in the MCP23008
      Wire.write(value);  // writes to the register in the MCP23008
      Wire.endTransmission(); // tells the MCP23008 we're done
    } // End of Register write method.

    byte MCPRead(byte RegAddress){ // "RegAddress" is the address of the device's register.
      Wire.beginTransmission(MCPaddress); // wakes up the MCP23008
      Wire.write(RegAddress); // sets the register pointer in the MCP23008
      Wire.endTransmission();
      Wire.requestFrom(MCPaddress,1); // tell MCP23008 to send byte from current register
      byte val = Wire.read();
      return val; // return the value of the register
    } // End of Register read method.
    
}; //  End of CLASS DEFINITION - REGISTER.
// Note the semicolon after the } to mark the end of a class definition
//////////////////////////////
