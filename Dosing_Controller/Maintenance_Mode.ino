void maintenanceMode() {
  if (oldMode != 2) {  // Display an into page for 3 seconds.
    oldMode = 2;
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Maintenance Mode");
    lcd.setCursor(0, 2);
    lcd.print("Adjust the time");
    lcd.setCursor(0, 3);
    lcd.print("durations for stages");
    delay(3000);  //  Pause so the display can be read.
    lcd.clear();
    lcd.setCursor(0,3);
    lcd.print(maintenanceMenu1);
    startMtceFlag=true;
    MtcePage=1; // Resets maintenece mode to first page.
  }
  
  byte d = SpareIO.MCPRead(GPIO); // Read the the pushbutton port.
  if(bitRead(d, pbRight)){ // Read the "Next" pushbutton.
    delay(pbDelay); // If the button was depressed, aollow time to release the pushbutton. 
    startMtceFlag=true;  // Flag will be clearded at the begining of a maintenance page after page is initialized.
    MtcePage += 1;
    if(MtcePage>23){MtcePage=1;}
  }
  if(bitRead(d, pbLeft)){ // Read the "Previos" pushbutton.
    delay(pbDelay); // If the button was depressed, aollow time to release the pushbutton. 
    startMtceFlag=true;
    MtcePage -= 1;
    if(MtcePage<1){MtcePage=23;}
  }
  bool mFlag=false;

  switch (MtcePage) {
    case 1:  //  Display Maintenance Page 1
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        flush1.display(1);
        startMtceFlag=false;
      }  
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=flush1.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        flush1.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(flush1.memBase, flush1.count);
      }
      break;
    case 2:  //  Display Maintenance Page 2
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        SodaPmp.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=SodaPmp.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        SodaPmp.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(SodaPmp.memBase, SodaPmp.count);
      }
     break;
    case 3:  //  Dsiplay Maintenance Page 3
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        flush2.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=flush2.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        flush2.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(flush2.memBase, flush2.count);
      }
      break;
    case 4:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        Part_C.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=Part_C.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        Part_C.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(Part_C.memBase, Part_C.count);
      }
      break;
    case 5:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        flush3.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=flush3.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        flush3.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(flush3.memBase, flush3.count);
      }
      break;
    case 6:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        vinegar.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=vinegar.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        vinegar.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(vinegar.memBase, vinegar.count);
      }
      break;
    case 7:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        flush4.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=flush4.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        flush4.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(flush4.memBase, flush4.count);
      }
      break;
    case 8:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        phyto.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=phyto.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        phyto.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(phyto.memBase, phyto.count);
      }
      break;
    case 9:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        phytoSalt.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=phytoSalt.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        phytoSalt.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(phytoSalt.memBase, phytoSalt.count);
      }
      break;
    case 10:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        flush5.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=flush5.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        flush5.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(flush5.memBase, flush5.count);
      }
      break;
    case 11:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        CalcmPmp.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=CalcmPmp.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        CalcmPmp.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(CalcmPmp.memBase, CalcmPmp.count);
      }
      break;
    case 12:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        frshWtr.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=frshWtr.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        frshWtr.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(frshWtr.memBase,frshWtr.count);
      }
      break;
    case 13:
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        FinalFlush.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=FinalFlush.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        FinalFlush.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(FinalFlush.memBase, FinalFlush.count);
      }
      break;
    case 14: // Predator_Flush1
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        Predator_Flush1.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=Predator_Flush1.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        Predator_Flush1.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(Predator_Flush1.memBase, Predator_Flush1.count);
      }
      break;
    case 15: // Predator_Phyto
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        Predator_Phyto.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=Predator_Phyto.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        Predator_Phyto.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(Predator_Phyto.memBase, Predator_Phyto.count);
      }
      break;
    case 16: // Predator_Flush2
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        Predator_Flush2.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=Predator_Flush2.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        Predator_Flush2.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(Predator_Flush2.memBase, Predator_Flush2.count);
      }
      break;
    case 17:  // Predator_Vinegar
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        Predator_Vinegar.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=Predator_Vinegar.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        Predator_Vinegar.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(Predator_Vinegar.memBase, Predator_Vinegar.count);
      }
      break;
    case 18: // Predator_Flush3
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        Predator_Flush3.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=Predator_Flush3.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        Predator_Flush3.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(Predator_Flush3.memBase, Predator_Flush3.count);
      }
      break;
    case 19:  // Predator_Spare
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        Predator_Spare.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=FinalFlush.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        Predator_Spare.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(Predator_Spare.memBase, Predator_Spare.count);
      }
    case 20:  // Predator_Flush4
      if(startMtceFlag==true){
        lcd.setCursor(0,0);
        lcd.print(maintenanceHeader);
        displayShortNum(MtcePage,18,0);
        Predator_Flush4.display(1);
        startMtceFlag=false;
      }
      while(bitRead(SpareIO.MCPRead(GPIO), pbCenter)){
        mFlag=true;
      }
      if(mFlag){ // Examine the center (Edit) pushbutton.
        mFlag=false;
        int newCount=Predator_Flush4.count;
        displayNum(newCount, 15, 2);
        newCount = adjustNumber(newCount); // The 'adjustNumber" procedure is located in "other_procedures.ino".
        Predator_Flush4.count = newCount;
        displayNum(newCount, 15, 1);
        DosEEPROM.memWrite(Predator_Flush4.memBase, Predator_Flush4.count);
      }
      break;
    case 21: // Adjust clock time and start time;
      if(startMtceFlag==true){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Clock Time: ");
        lcd.setCursor(0,1);
        lcd.print("Start Time: ");
        lcd.setCursor(0,2);
        lcd.print(blankLine);
        lcd.setCursor(0,3);
        lcd.print(maintenanceMenu1); // "Previos Edit    Next"
        startMtceFlag=false;
      }
      lcd.setCursor(12,0);
      displayClockTime();
      lcd.setCursor(12,1);
      displayStartTime();
      d = SpareIO.MCPRead(GPIO); // Examine the center (Edit) pushbutton, want to edit the clock or the sart times.
      delay(pbDelay); // Give time to remove finger from center pushbutton
      if(bitRead(d,pbCenter)){ // 
        timeAdjust(); // Located in other_procdures.ino.
      }
      break;
    case 22: // Temperature
      if(startMtceFlag==true){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Box temp:     ");
        lcd.setCursor(0,1);
        lcd.print("Temp setting: ");
        lcd.setCursor(0,3);
        lcd.print(maintenanceMenu1); // "Previos Edit    Next"
        startMtceFlag=false;
      }
      lcd.setCursor(15,0);
      lcd.print(tempF);
      lcd.setCursor(15,1);
      lcd.print(tempSetpoint);
      d = SpareIO.MCPRead(GPIO); // Examine the center (Edit) pushbutton, want to edit the clock or the sart times.
      delay(pbDelay); // Give time to remove finger from center pushbutton
      if(bitRead(d,pbCenter)){ // 
        //
      }
      break;
    case 23: // Not used yet.
      lcd.clear();
      lcd.setCursor(0,0);
      displayClockTime();
      lcd.setCursor(0,3);
      lcd.print("Empty page.");
      delay(500);
      break;
  }  //   End of switch...case structure.
}  //  End of maintenanceMode().
