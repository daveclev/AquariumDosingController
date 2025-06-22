
//  The M24512 I2C EEPROM device can store 64k bytes.
//  Memory locations are addressed with 16 bit address.
//  The MSByte of the address identifies a page.  so;
//   there are 256 pages, each page having 256 locations.

//  EEPROM MEMORY MAP
//  LOCATION:  CONTENT:
//   10         stage 1 count
//   1
//  

class M24512{ // The EEPROM class will have only three parameters, listed below.
  public:
    byte memI2Caddress; //this is the device I2C address
    int memAddress; // the memory location within the 512 device
//    byte mData[];
    
    M24512(byte x){ // Constructor for the 512 memory class
      memI2Caddress = x; // the I2C address for the device
    } // End of Register constructor.

    // The memWrite() method is overloaded to allow one command to be used to store a byte, or an interger, or a boolean variable.
    // The distinction between the methods is through the type of the parameter passed to the method.
    void memWrite(int memAddress, byte value){  // Write one integer value to the I2C memory
      Wire.beginTransmission(memI2Caddress); //  Wake up the 512 I2C memory device.
      Wire.write(highByte(memAddress)); // Set the memory location pointer.
      Wire.write(lowByte(memAddress));
      Wire.write(value); 
      Wire.endTransmission();
      delay(5);  // Experimental.  3 works, 2 doesn't work.
    } // End of mamWrite() method.

    void memWrite(int memAddress, int value){  // Write one integer value to the I2C memory
      Wire.beginTransmission(memI2Caddress); //  Wake up the 512 I2C memory device.
      Wire.write(highByte(memAddress)); // Set the memory location pointer.
      Wire.write(lowByte(memAddress));
      Wire.write(highByte(value)); 
      Wire.write(lowByte(value));
      Wire.endTransmission();
      delay(5);  // Experimental.  3 works, 2 doesn't work.
    } // End of mamWrite() method.

    void memWrite(int memAddress, bool value){  // Write one integer value to the I2C memory
      Wire.beginTransmission(memI2Caddress); //  Wake up the 512 I2C memory device.
      Wire.write(highByte(memAddress)); // Set the memory location pointer.
      Wire.write(lowByte(memAddress));
      if(value){
        Wire.write(0x01);}
        else{Wire.write(0x00);}
      Wire.endTransmission();
      delay(5);  // Experimental.  3 works, 2 doesn't work.
    } // End of mamWrite() bool method.

  byte memReadByte(int memAddress){ // "RegAddress" is the address of the device's register.
      Wire.beginTransmission(memI2Caddress); // Wake up the I2C EEPROM.
      Wire.write(highByte(memAddress)); // Set the memory location pointer.  
      Wire.write(lowByte(memAddress));
      Wire.endTransmission();
      Wire.requestFrom(memI2Caddress,1); // tell device to send one byte from current memory pointer.
      byte val = Wire.read();
      return val; // return the value of the register
    } // End of Register read method.

    int memReadInt(int memAddress){ // "RegAddress" is the address of the device's register.
      Wire.beginTransmission(memI2Caddress); // Wake up the I2C EEPROM.
      Wire.write(highByte(memAddress)); // Set the memory location pointer.  
      Wire.write(lowByte(memAddress));
      Wire.endTransmission();
      Wire.requestFrom(memI2Caddress,2); // tell device to send two bytes starting at the current memory pointer.
      int val = 256 * Wire.read() + Wire.read();
      return val; // return the value of the register
    } // End of memReadInt() method.

    bool memReadBool(byte memAddress){ // "RegAddress" is the address of the device's register.
      Wire.beginTransmission(memI2Caddress); // Wake up the I2C EEPROM.
      Wire.write(highByte(memAddress)); // Set the memory location pointer.  
      Wire.write(lowByte(memAddress));
      Wire.endTransmission();
      Wire.requestFrom(memI2Caddress,1); // tell device to send one byte from current memory pointer.
      bool val;
      if(Wire.read()){val = true;}
        else{val = false;}
      return val; // return the value of the register
    } // End of memReadBool method.

}; //  End of M24512 class definition.


 
