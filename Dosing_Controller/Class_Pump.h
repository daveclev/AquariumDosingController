/////////////////////////////
// CLASS DEFINITION - Pump
//////////////////////////////

class Pump{ // An instance of Pump class will be created for each output.
  public:
    byte outputPin; // OutputPin is the output that the pump is wired to.
    
    Pump(byte x){ // Constructor for Register class
      outputPin = x; // the output that the pump is connected to
    } // End of Pump constructor.

    /*
      Output:     Schematic     Device    Pin       I2C
      M0 - M7     Dosing1        U12     GP0-GP7    0x24
      M8 - M15    Dosing2        U10     GP0-GP7    0x22
    */

    //  Turn on an output pin.  
    //  Simply sending 0x08 to a register will turn on that bit of a register, but will turn off all other bits. 
    //  To preserve state of other bits we must "OR" existing content of of the register to a mask such as 0b00001000.
    void ON(){ // Turn on the pump
      byte I2C; // This will be the I2C address of the appropriate IO Expader, U12 (outputs -8) or U10 (outputs 9-16).
      byte outP; // This will be the IO pin on the IO expander.
      byte p; // This variable will be the value at the GPIO, the appropriate bit (outP) needs to be set to turn on the pump.
      if (outputPin>7){
        I2C = 0x22; // Controller outputs 8-15 are on U10, 
        outP = outputPin -8; // Shifts outputs 8-15 to pins 0-7 on U10.
      }else{
        I2C = 0x24; // Controller outputs 9-16 are on U12, 
        outP = outputPin; // Controller outputs 0-7 map directly to pins on U12.
      }
      Wire.beginTransmission(I2C); // Wake up the IO device.
      Wire.write(0x09); // Point to the GPIO register 0x09.
      Wire.endTransmission();
      Wire.requestFrom(I2C, 1); // Tell the IO device to send one byte.
      p=Wire.read(); // Read the byte sent from the IO device.
      p=bitSet(p,outP);
      Wire.beginTransmission(I2C);
      Wire.write(0x09);
      Wire.write(p); // Write the new value to the IO device.
      Wire.endTransmission();
      } //  End of ON method.

    void OFF(){ // Turn on the pump
      byte I2C; // This will be the I2C address of the appropriate IO Expader, U12 (outputs -8) or U10 (outputs 9-16).
      byte outP; // This will be the IO pin on the IO expander.
      byte p; // This variable will be the value at the GPIO, the appropriate bit (outP) needs to be set to turn on the pump.
      if (outputPin>7){
        I2C = 0x22; // Controller outputs 8-15 are on U10, 
        outP = outputPin -8; // Shifts outputs 8-15 to pins 0-7 on U10.
      }else{
        I2C = 0x24; // Controller outputs 9-16 are on U12, 
        outP = outputPin; // Controller outputs 0-7 map directly to pins on U12.
      }
      Wire.beginTransmission(I2C); // Wake up the IO device.
      Wire.write(0x09); // Point to the GPIO register 0x09.
      Wire.endTransmission();
      Wire.requestFrom(I2C, 1); // Tell the IO device to send one byte.
      p=Wire.read(); // Read the byte sent from the IO device.
      p=bitClear(p,outP);
      Wire.beginTransmission(I2C);
      Wire.write(0x09);
      Wire.write(p); // Write the new value to the IO device.
      Wire.endTransmission();
      } //  End of OFF method.


}; //  End of CLASS DEFINITION - PUMP.
