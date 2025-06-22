/////////////////////////
// VARIOUS PROCEDURES
/////////////////////////

//  This "displayNum" method displays a byte, right justified, by adding spaces.  Max number is 999.
void displayNum(byte number, byte col, byte row) {
  lcd.setCursor(col, row);  //Set cursor to character location passed to the procedure, column 0-19 and row 0-3
  if (number < 10) {
    lcd.print("  ");
    lcd.print(number);
  } else if (number < 100) {
    lcd.print(" ");
    lcd.print(number);
  } else {
    lcd.print(number);
  }
}

// This "displayNum" method displays inteter.  The method is overloaded to allow printing bytes or intergers.
void displayNum(int number, byte col, byte row) {
  lcd.setCursor(col, row);  //Set cursor to character location passed to the procedure, column 0-19 and row 0-3
  if (number < 10) {
    lcd.print("    ");
    lcd.print(number);
  } else if (number < 100) {
    lcd.print("   ");
    lcd.print(number);
  } else if (number < 1000) {
    lcd.print("  ");
    lcd.print(number);
  } else if (number < 1000) {
    lcd.print(" ");
    lcd.print(number);
  } else {
    lcd.print(number);
  }
} // End of diplayNum procedure.

//  This "displayShortNum" method displays a byte, right justified, by adding spaces.  Max number is 999.
void displayShortNum(byte number, byte col, byte row) {
  lcd.setCursor(col, row);  //Set cursor to character location passed to the procedure, column 0-19 and row 0-3
  if (number < 10) {
    lcd.print(" ");
    lcd.print(number);
  } else {
    lcd.print(number);
  }
}


/////////////
//  ENCODER procedure, "adjustNumber"
/////////////
//  The "adjustNumber" procedure receives an integer from the calling statement and
//  adjusts that number as the rotary encoder is rotated.  Pressing the rotary encoder
//  provides a coarse (10x) adjustment.

int adjustNumber(int oldNumber) {
  encoderCount = oldNumber; // Initiates encoder ISR to begin at the value passed to "adjustNumber" procedure.  
  int returnValue; // At end of procedure, the procedure will return either the new encoder value or the original number passed to "adjustNumber".
  bool runFlag = true; // The "while" loop will continue cycling until the runFlag is cleared by depressing either the "Accept" or "Cancel" pushbuttons.
  lcd.setCursor(5,2);
  lcd.print("New Value:");
  lcd.setCursor(0,3);
  lcd.print(maintenanceMenu2); // Display function button names, "Cancl" and "Accpt"
  while(runFlag==true){
    returnValue = encoderCount; // encoderCount is updated by the interrupt service routine as the encoder is rotated.
    displayNum(encoderCount,15,2);
    byte n = SpareIO.MCPRead(GPIO); // Read the CANCEL and ACCEPT pushbuttons to see if we are done adjusting.
    delay(pbDelay);
    if (bitRead(n, pbRight)){ //  See if the Accept (right) button is pressed
      runFlag=false;
      displayNum(encoderCount,16,1); // display the new value
    }
    if (bitRead(n, pbCenter)){ //  See if Cancel (center) button is pressed
      runFlag=false;
      returnValue = oldNumber;  // Resort back to the original number
    }   
  }
  lcd.setCursor(0,2);
  lcd.print(blankLine);// declared in main program header
  lcd.setCursor(0,3);
  lcd.print(maintenanceMenu1); //  Display "Next", "Edit", "Previos"
  return returnValue;
}  // End of adjustNumber() procedure.

int adjustTimeNumber(int oldNumber) {
  encoderCount = oldNumber; // Initiates encoder ISR to begin at the value passed to "adjustTimeNumber" procedure.  
  int returnValue; // At end of procedure, the procedure will return either the new encoder value or the original number passed to "adjustNumber".
  bool runFlag = true; // The "while" loop will continue cycling until the runFlag is cleared by depressing either the "Accept" or "Cancel" pushbuttons.
  lcd.setCursor(5,2);
  lcd.print("New Value:");
  lcd.setCursor(0,3);
  lcd.print(maintenanceMenu2); // Display function button names, "Cancl" and "Accpt"
  while(runFlag==true){
    returnValue = encoderCount; // encoderCount is updated by the interrupt service routine as the encoder is rotated.
    displayNum(encoderCount,15,2);
    byte n = SpareIO.MCPRead(GPIO); // Read the CANCEL and ACCEPT pushbuttons to see if we are done adjusting.
    delay(pbDelay);
    if (bitRead(n, pbRight)){ //  See if the Accept (right) button is pressed
      runFlag=false;
      displayNum(encoderCount,15,1); // display the new value
    }
    if (bitRead(n, pbCenter)){ //  See if Cancel (center) button is pressed
      runFlag=false;
      returnValue = oldNumber;  // Resort back to the original number
    }   
  }
  lcd.setCursor(0,2);
  lcd.print(blankLine); // Declared in main program header
  lcd.setCursor(0,3);
  lcd.print(maintenanceMenu1); //  Display "Next", "Edit", "Previos"
  return returnValue;
}  // End of adjustNumber() procedure.

void displayClockTime(){
  //rtc.updateTime();
  ss = rtc.BCDtoDEC(0b01111111 & rtc.readRegister(0x08)); // Strip out bit  7 then convert to DEC.
  mm = rtc.BCDtoDEC(0b01111111 & rtc.readRegister(0x09));
  hh = rtc.BCDtoDEC(0b01111111 & rtc.readRegister(0x0A));
  if(hh<10){lcd.print("0");}
  lcd.print(hh);
  lcd.print(":");
  if(mm<10){lcd.print("0");}
  lcd.print(mm);
  lcd.print(":");
  if(ss<10){lcd.print("0");}
  lcd.print(ss);
} // End of displayClockTime() procedure.


void displayStartTime(){
  if(startHr<10){lcd.print("0");}
  lcd.print(startHr);
  lcd.print(":");
  if(startMin<10){lcd.print("0");}
  lcd.print(startMin);
  lcd.print(":");
  if(startSec<10){lcd.print("0");}
  lcd.print(startSec);
} // End of displayStartTime() procedure.

void timeAdjust(){
  lcd.clear();
  lcd.setCursor(0,2);
  lcd.print("Edit            Edit");
  lcd.setCursor(0,3);
  lcd.print("Clock   Exit   Start");
  bool outerLoopFlag = true;
  bool innerLoopFlag = true; //  Will be used while editing either the clock time or the start time.
  while (outerLoopFlag==true){ // runFlagTA will be cleared when we no longer want to edit either the clock or the start times.
    byte n = SpareIO.MCPRead(GPIO); //  Read the pushbuttons to determine if we edit clock time, exit, or edit start time.
    if (bitRead(n, pbCenter)){  //  See if the Return (center) button is pressed.
      delay(pbDelay); // time to release the pushbutton.
      outerLoopFlag = false; // exit the outer "while" loop. 
    }  
    if (bitRead(n, pbLeft)){  //  See if the left (edit the clock time) button is pressed.
      delay(pbDelay); // time to release the pushbutton.
      while(innerLoopFlag==true){  // Left pushbutton: edit clock time. Begins inner "while" loop.
       lcd.setCursor(0,0);
       lcd.print("   Edit Clock time  ");
       lcd.setCursor(0,3);
       lcd.print("Hour   Exit   Minute");
       byte m = SpareIO.MCPRead(GPIO); //  Read the pushbuttons, to see if we edit the clock hours, exit, or edit the clock minutes.
       if bitRead(m, pbLeft){ // edit the hours value.
        delay(pbDelay); // Time to release pushbutton.
        int oldHour = rtc.getHours();
        int newHour = adjustTimeNumber(oldHour); // Program is held in a "while" loop inside the adjustTimeNumber procedure as encoder is used.
        rtc.setHours(newHour);
       }
       if bitRead(m, pbRight){ // Edit the clock minutes value.
        delay(pbDelay); // Time to release pushbutton.
        int oldMinute = rtc.getMinutes();
        int newMinute = adjustTimeNumber(oldMinute); // Program is held in a "while" loop inside the adjustTimeNumber procedure as encoder is used.
        rtc.setMinutes(newMinute);
       }
       if bitRead(m, pbCenter){ // Done editing the clock time.
        innerLoopFlag=false;
       }
      } 
    }  
    if (bitRead(n, pbRight)){  //  See if the "Start" (right) button is pressed to begin editing the start time.
      delay(pbDelay); // time to release the pushbutton.
      while(innerLoopFlag==true){ // Right pushbutton: edit alarm time.
       lcd.setCursor(0,0);
       lcd.print("Edit Cycle Strt time");
       lcd.setCursor(0,3);
       lcd.print("Hour   Exit   Minute");
       byte m = SpareIO.MCPRead(GPIO); //  Read the pushbuttons.
       if bitRead(m, pbLeft){ // edit the hours value.
        delay(pbDelay); // Time to release pushbutton.
        int oldHour = startHr;
        startHr = adjustTimeNumber(oldHour); // Program is held in "while" loop as encoder is used.
        DosEEPROM.memWrite(startHrMem,startHr);
       }
       if bitRead(m, pbRight){ // Edit the clock minutes value.
        delay(pbDelay); // Time to release pushbutton.
        int oldMinute = startMin;
        startMin = adjustTimeNumber(oldMinute); // Program is held in "while" loop as encoder is used.
        DosEEPROM.memWrite(startMinMem,startMin);
       }
       if bitRead(m, pbCenter){ // Done editing the clock time.
        innerLoopFlag=false;
       }
      } 
    }  
  }
} // End of timeAdjust() procedure.

void retrieveEEPROM(){ // This procedure is called from the "Start" routine and loads the values stored in EEPROM w.
  lcd.setCursor(5,0);
  lcd.print("Loading...");
  lcd.setCursor(0,1);
  lcd.print("#");
  delay(150);
  currentStage = DosEEPROM.memReadByte(currentStageMem); //  Address 0x0002
  startHr = DosEEPROM.memReadInt(startHrMem); //  Address 0x0004
  startMin = DosEEPROM.memReadInt(startMinMem); //  Address 0x0006
  startSec = DosEEPROM.memReadInt(startSecMem); //  Address 0x0008
  tempSetpoint = DosEEPROM.memReadInt(tempSetpointMem); //  Address 0x000A
  cycleCounter = DosEEPROM.memReadInt(cycleCounterMem); //  Address 0x000C
  flush1.count = DosEEPROM.memReadInt(flush1.memBase); 
  flush1.countDown = DosEEPROM.memReadInt(flush1.memBase+2); 
  flush1.running = DosEEPROM.memReadBool(flush1.memBase+4); 
  flush1.complete = DosEEPROM.memReadBool(flush1.memBase+5); 
  SodaPmp.count = DosEEPROM.memReadInt(SodaPmp.memBase); 
  SodaPmp.countDown = DosEEPROM.memReadInt(SodaPmp.memBase+2); 
  SodaPmp.running = DosEEPROM.memReadBool(SodaPmp.memBase+4); 
  SodaPmp.complete = DosEEPROM.memReadBool(SodaPmp.memBase+5); 
  lcd.print("#");
  delay(150);
  flush2.count = DosEEPROM.memReadInt(flush2.memBase); 
  flush2.countDown = DosEEPROM.memReadInt(flush2.memBase+2); 
  flush2.running = DosEEPROM.memReadBool(flush2.memBase+4); 
  flush2.complete = DosEEPROM.memReadBool(flush2.memBase+5); 
  lcd.print("#");
  delay(150);
  Part_C.count = DosEEPROM.memReadInt(Part_C.memBase); 
  Part_C.countDown = DosEEPROM.memReadInt(Part_C.memBase+2); 
  Part_C.running = DosEEPROM.memReadBool(Part_C.memBase+4); 
  Part_C.complete = DosEEPROM.memReadBool(Part_C.memBase+5); 
  lcd.print("#");
  delay(150);
  flush3.count = DosEEPROM.memReadInt(flush3.memBase); 
  flush3.countDown = DosEEPROM.memReadInt(flush3.memBase+2); 
  flush3.running = DosEEPROM.memReadBool(flush3.memBase+4); 
  flush3.complete = DosEEPROM.memReadBool(flush3.memBase+5); 
  lcd.print("#");
  delay(150);
  vinegar.count = DosEEPROM.memReadInt(vinegar.memBase); 
  vinegar.countDown = DosEEPROM.memReadInt(vinegar.memBase+2); 
  vinegar.running = DosEEPROM.memReadBool(vinegar.memBase+4); 
  vinegar.complete = DosEEPROM.memReadBool(vinegar.memBase+5); 
  lcd.print("#");
  delay(150);
  flush4.count = DosEEPROM.memReadInt(flush4.memBase); 
  flush4.countDown = DosEEPROM.memReadInt(flush4.memBase+2); 
  flush4.running = DosEEPROM.memReadBool(flush4.memBase+4); 
  flush4.complete = DosEEPROM.memReadBool(flush4.memBase+5); 
  lcd.print("#");
  delay(150);
  phyto.count = DosEEPROM.memReadInt(phyto.memBase); 
  phyto.countDown = DosEEPROM.memReadInt(phyto.memBase+2); 
  phyto.running = DosEEPROM.memReadBool(phyto.memBase+4); 
  phyto.complete = DosEEPROM.memReadBool(phyto.memBase+5); 
  lcd.print("#");
  delay(150);
  phytoSalt.count = DosEEPROM.memReadInt(phytoSalt.memBase); 
  phytoSalt.countDown = DosEEPROM.memReadInt(phytoSalt.memBase+2); 
  phytoSalt.running = DosEEPROM.memReadBool(phytoSalt.memBase+4); 
  phytoSalt.complete = DosEEPROM.memReadBool(phytoSalt.memBase+5); 
  lcd.print("#");
  delay(150);
  flush5.count = DosEEPROM.memReadInt(flush5.memBase); 
  flush5.countDown = DosEEPROM.memReadInt(flush5.memBase+2); 
  flush5.running = DosEEPROM.memReadBool(flush5.memBase+4); 
  flush5.complete = DosEEPROM.memReadBool(flush5.memBase+5); 
  lcd.print("#");
  delay(150);
  CalcmPmp.count = DosEEPROM.memReadInt(CalcmPmp.memBase); 
  CalcmPmp.countDown = DosEEPROM.memReadInt(CalcmPmp.memBase+2); 
  CalcmPmp.running = DosEEPROM.memReadBool(CalcmPmp.memBase+4); 
  CalcmPmp.complete = DosEEPROM.memReadBool(CalcmPmp.memBase+5); 
  lcd.print("#");
  delay(150);
  frshWtr.count = DosEEPROM.memReadInt(frshWtr.memBase); 
  frshWtr.countDown = DosEEPROM.memReadInt(frshWtr.memBase+2); 
  frshWtr.running = DosEEPROM.memReadBool(frshWtr.memBase+4); 
  frshWtr.complete = DosEEPROM.memReadBool(frshWtr.memBase+5); 
  lcd.print("#");
  delay(150);
  FinalFlush.count = DosEEPROM.memReadInt(FinalFlush.memBase); 
  FinalFlush.countDown = DosEEPROM.memReadInt(FinalFlush.memBase+2); 
  FinalFlush.running = DosEEPROM.memReadBool(FinalFlush.memBase+4); 
  FinalFlush.complete = DosEEPROM.memReadBool(FinalFlush.memBase+5); 
  lcd.print("#");
  delay(150);
  Predator_Flush1.count = DosEEPROM.memReadInt(Predator_Flush1.memBase); 
  Predator_Flush1.countDown = DosEEPROM.memReadInt(Predator_Flush1.memBase+2); 
  Predator_Flush1.running = DosEEPROM.memReadBool(Predator_Flush1.memBase+4); 
  Predator_Flush1.complete = DosEEPROM.memReadBool(Predator_Flush1.memBase+5); 
  lcd.print("#");
  delay(150);
  Predator_Phyto.count = DosEEPROM.memReadInt(Predator_Phyto.memBase); 
  Predator_Phyto.countDown = DosEEPROM.memReadInt(Predator_Phyto.memBase+2); 
  Predator_Phyto.running = DosEEPROM.memReadBool(Predator_Phyto.memBase+4); 
  Predator_Phyto.complete = DosEEPROM.memReadBool(Predator_Phyto.memBase+5); 
  lcd.print("#");
  delay(150);
  Predator_Flush2.count = DosEEPROM.memReadInt(Predator_Flush2.memBase); 
  Predator_Flush2.countDown = DosEEPROM.memReadInt(Predator_Flush2.memBase+2); 
  Predator_Flush2.running = DosEEPROM.memReadBool(Predator_Flush2.memBase+4); 
  Predator_Flush2.complete = DosEEPROM.memReadBool(Predator_Flush2.memBase+5); 
  lcd.print("#");
  delay(150);
  Predator_Vinegar.count = DosEEPROM.memReadInt(Predator_Vinegar.memBase); 
  Predator_Vinegar.countDown = DosEEPROM.memReadInt(Predator_Vinegar.memBase+2); 
  Predator_Vinegar.running = DosEEPROM.memReadBool(Predator_Vinegar.memBase+4); 
  Predator_Vinegar.complete = DosEEPROM.memReadBool(Predator_Vinegar.memBase+5); 
  lcd.print("#");
  delay(150);
  Predator_Flush3.count = DosEEPROM.memReadInt(Predator_Flush3.memBase); 
  Predator_Flush3.countDown = DosEEPROM.memReadInt(Predator_Flush3.memBase+2); 
  Predator_Flush3.running = DosEEPROM.memReadBool(Predator_Flush3.memBase+4); 
  Predator_Flush3.complete = DosEEPROM.memReadBool(Predator_Flush3.memBase+5); 
  lcd.print("#");
  delay(150);
  Predator_Spare.count = DosEEPROM.memReadInt(Predator_Spare.memBase); 
  Predator_Spare.countDown = DosEEPROM.memReadInt(Predator_Spare.memBase+2); 
  Predator_Spare.running = DosEEPROM.memReadBool(Predator_Spare.memBase+4); 
  Predator_Spare.complete = DosEEPROM.memReadBool(Predator_Spare.memBase+5); 
  lcd.print("#");
  delay(150);
  Predator_Flush4.count = DosEEPROM.memReadInt(Predator_Flush4.memBase); 
  Predator_Flush4.countDown = DosEEPROM.memReadInt(Predator_Flush4.memBase+2); 
  Predator_Flush4.running = DosEEPROM.memReadBool(Predator_Flush4.memBase+4); 
  Predator_Flush4.complete = DosEEPROM.memReadBool(Predator_Flush4.memBase+5); 
  lcd.print("#");
  delay(150);
  wait.count = DosEEPROM.memReadInt(0x00A0); 
  wait.countDown = DosEEPROM.memReadInt(0x00A2); 
  wait.running = DosEEPROM.memReadBool(0x00A4); 
  wait.complete = DosEEPROM.memReadBool(0x00A5); 
  //currentStage = DosEEPROM.memReadByte(0x0002);
}  // End of retreiveEEPROM() procedure.


// This function is only used to store an initial set of values in an empty EEPROM.
void initializeEEPROM(){
  DosEEPROM.memWrite(0x0004, startHr); // Initialize hour for start time, startHr, int
  DosEEPROM.memWrite(0x0006, startMin); // Initialize minutes for start time, startMin, int.
  DosEEPROM.memWrite(0x0008, startSec); // Initialize minusecodstes for start time, startSec, int.
  DosEEPROM.memWrite(currentStageMem, currentStage);
  DosEEPROM.memWrite(tempSetpointMem,tempSetpoint);
  DosEEPROM.memWrite(currentStageMem, 21);
  DosEEPROM.memWrite(cycleCounterMem,0);
  DosEEPROM.memWrite(flush1.memBase, flush1.count); // stores an integer, two bytes
  DosEEPROM.memWrite(flush1.memBase+2, flush1.countDown); // stores an integer, two bytes
  DosEEPROM.memWrite(flush1.memBase+4, flush1.running); // stores boolean, one byte
  DosEEPROM.memWrite(flush1.memBase+5, flush1.complete); // stores boolean, one byte

  DosEEPROM.memWrite(SodaPmp.memBase, SodaPmp.count); 
  DosEEPROM.memWrite(SodaPmp.memBase+2, SodaPmp.countDown); 
  DosEEPROM.memWrite(SodaPmp.memBase+4, SodaPmp.running); 
  DosEEPROM.memWrite(SodaPmp.memBase+5, SodaPmp.complete); 

  DosEEPROM.memWrite(flush2.memBase, flush2.count); 
  DosEEPROM.memWrite(flush2.memBase+2, flush2.countDown); 
  DosEEPROM.memWrite(flush2.memBase+4, flush2.running); 
  DosEEPROM.memWrite(flush2.memBase+5, flush2.complete); 

  DosEEPROM.memWrite(Part_C.memBase, Part_C.count); 
  DosEEPROM.memWrite(Part_C.memBase+2, Part_C.countDown); 
  DosEEPROM.memWrite(Part_C.memBase+4, Part_C.running); 
  DosEEPROM.memWrite(Part_C.memBase+5, Part_C.complete); 

  DosEEPROM.memWrite(flush3.memBase, flush3.count); 
  DosEEPROM.memWrite(flush3.memBase+2, flush3.countDown); 
  DosEEPROM.memWrite(flush3.memBase+4, flush3.running); 
  DosEEPROM.memWrite(flush3.memBase+5, flush3.complete); 

  DosEEPROM.memWrite(vinegar.memBase, vinegar.count); 
  DosEEPROM.memWrite(vinegar.memBase+2, vinegar.countDown); 
  DosEEPROM.memWrite(vinegar.memBase+4, vinegar.running); 
  DosEEPROM.memWrite(vinegar.memBase+5, vinegar.complete); 

  DosEEPROM.memWrite(flush4.memBase, flush4.count); 
  DosEEPROM.memWrite(flush4.memBase+2, flush4.countDown); 
  DosEEPROM.memWrite(flush4.memBase+4, flush4.running); 
  DosEEPROM.memWrite(flush4.memBase+5, flush4.complete); 

  DosEEPROM.memWrite(phyto.memBase, phyto.count); 
  DosEEPROM.memWrite(phyto.memBase+2, phyto.countDown); 
  DosEEPROM.memWrite(phyto.memBase+4, phyto.running); 
  DosEEPROM.memWrite(phyto.memBase+5, phyto.complete); 
 
  DosEEPROM.memWrite(phytoSalt.memBase, phytoSalt.count); 
  DosEEPROM.memWrite(phytoSalt.memBase+2, phytoSalt.countDown); 
  DosEEPROM.memWrite(phytoSalt.memBase+4, phytoSalt.running); 
  DosEEPROM.memWrite(phytoSalt.memBase+5, phytoSalt.complete); 

  DosEEPROM.memWrite(flush5.memBase, flush5.count); 
  DosEEPROM.memWrite(flush5.memBase+2, flush5.countDown); 
  DosEEPROM.memWrite(flush5.memBase+4, flush5.running); 
  DosEEPROM.memWrite(flush5.memBase+5, flush5.complete); 

  DosEEPROM.memWrite(CalcmPmp.memBase, CalcmPmp.count); 
  DosEEPROM.memWrite(CalcmPmp.memBase+2, CalcmPmp.countDown); 
  DosEEPROM.memWrite(CalcmPmp.memBase+4, CalcmPmp.running); 
  DosEEPROM.memWrite(CalcmPmp.memBase+5, CalcmPmp.complete); 

  DosEEPROM.memWrite(frshWtr.memBase, frshWtr.count); 
  DosEEPROM.memWrite(frshWtr.memBase+2, frshWtr.countDown); 
  DosEEPROM.memWrite(frshWtr.memBase+4, frshWtr.running); 
  DosEEPROM.memWrite(frshWtr.memBase+5, frshWtr.complete); 
 
  DosEEPROM.memWrite(FinalFlush.memBase, FinalFlush.count); 
  DosEEPROM.memWrite(FinalFlush.memBase+2, FinalFlush.countDown); 
  DosEEPROM.memWrite(FinalFlush.memBase+4, FinalFlush.running); 
  DosEEPROM.memWrite(FinalFlush.memBase+5, FinalFlush.complete); 
  // new stages:
  DosEEPROM.memWrite(Predator_Flush1.memBase, Predator_Flush1.count); 
  DosEEPROM.memWrite(Predator_Flush1.memBase+2, Predator_Flush1.countDown); 
  DosEEPROM.memWrite(Predator_Flush1.memBase+4, Predator_Flush1.running); 
  DosEEPROM.memWrite(Predator_Flush1.memBase+5, Predator_Flush1.complete); 

  DosEEPROM.memWrite(Predator_Phyto.memBase, Predator_Phyto.count); 
  DosEEPROM.memWrite(Predator_Phyto.memBase+2, Predator_Phyto.countDown); 
  DosEEPROM.memWrite(Predator_Phyto.memBase+4, Predator_Phyto.running); 
  DosEEPROM.memWrite(Predator_Phyto.memBase+5, Predator_Phyto.complete); 
 
  DosEEPROM.memWrite(Predator_Flush2.memBase, Predator_Flush2.count); 
  DosEEPROM.memWrite(Predator_Flush2.memBase+2, Predator_Flush2.countDown); 
  DosEEPROM.memWrite(Predator_Flush2.memBase+4, Predator_Flush2.running); 
  DosEEPROM.memWrite(Predator_Flush2.memBase+5, Predator_Flush2.complete); 

  DosEEPROM.memWrite(Predator_Vinegar.memBase, Predator_Vinegar.count); 
  DosEEPROM.memWrite(Predator_Vinegar.memBase+2, Predator_Vinegar.countDown); 
  DosEEPROM.memWrite(Predator_Vinegar.memBase+4, Predator_Vinegar.running); 
  DosEEPROM.memWrite(Predator_Vinegar.memBase+5, Predator_Vinegar.complete); 

  DosEEPROM.memWrite(Predator_Flush3.memBase, Predator_Flush3.count); 
  DosEEPROM.memWrite(Predator_Flush3.memBase+2, Predator_Flush3.countDown); 
  DosEEPROM.memWrite(Predator_Flush3.memBase+4, Predator_Flush3.running); 
  DosEEPROM.memWrite(Predator_Flush3.memBase+5, Predator_Flush3.complete); 

  DosEEPROM.memWrite(Predator_Spare.memBase, Predator_Spare.count); 
  DosEEPROM.memWrite(Predator_Spare.memBase+2, Predator_Spare.countDown); 
  DosEEPROM.memWrite(Predator_Spare.memBase+4, Predator_Spare.running); 
  DosEEPROM.memWrite(Predator_Spare.memBase+5, Predator_Spare.complete); 
 
  DosEEPROM.memWrite(Predator_Flush4.memBase, Predator_Flush4.count); 
  DosEEPROM.memWrite(Predator_Flush4.memBase+2, Predator_Flush4.countDown); 
  DosEEPROM.memWrite(Predator_Flush4.memBase+4, Predator_Flush4.running); 
  DosEEPROM.memWrite(Predator_Flush4.memBase+5, Predator_Flush4.complete); 

} // End of initialieEEPROM() peocedure.
