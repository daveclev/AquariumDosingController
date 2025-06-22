void autoRun(){
  if(oldMode != 1){
    oldMode = 1;
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Auto Run Mode");
    lcd.setCursor(0,2);
    lcd.print("Pumps are controlled");
    lcd.setCursor(0,3);
    lcd.print(" automaically.");
    delay(3000);
    lcd.clear();
    lcd.setCursor(6,3);
    startStageFlag=true;
    currentStage=DosEEPROM.memReadByte(currentStageMem);
  }
    newmilli = millis();
  if (newmilli - oldmilli > 1000) {
    oldmilli = newmilli;
    pumpUpdate();  
  }

}  //  End of autoRun() procedure

void pumpUpdate(){
  switch (currentStage) {
    case 1: // Flush 1
      if (startStageFlag) {  // Initialize this stage;
      stageSetup();  // located at the end of Auto_Run_Mode.inl file
        flush1.display(1);
        lcd.setCursor(0, 2);  //Set cursor to character 0 on row
        lcd.print("Next Stage:");
        SodaPmp.display(3);
        flush1.countDown = flush1.count;
        // Turn on the appropriate pump
        Flush_BowFrontPump.ON();
      }
      flush1.update();        // Update the stage countdown
      if (flush1.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem, currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
      }
      break;
    case 2: // Soda Pump
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        SodaPmp.display(1);
        flush2.display(3);
        SodaPmp.countDown = SodaPmp.count;
        // Turn on the appropriate pump
        SodaPump.ON();
      }
      SodaPmp.update();        // Update the stage countdown
      if (SodaPmp.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem, currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
        SodaPump.OFF();
      }
      break;
    case 3: // Flush 2
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        flush2.display(1);
        Part_C.display(3);
        flush2.countDown = flush2.count;
        // Turn on the appropriate pump
      }
      flush2.update();        // Update the stage countdown
      if (flush2.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem, currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
      }
      break;
    case 4: // Part C
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        Part_C.display(1);
        flush3.display(3);
        Part_C.countDown = Part_C.count;
        // Turn on the appropriate pump
        PartCPump.ON();
      }
      Part_C.update();        // Update the stage countdown
      if (Part_C.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem, currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
        PartCPump.OFF();
      }
      break;
    case 5: // Flush 3
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        flush3.display(1);
        vinegar.display(3);
        flush3.countDown = flush3.count;
        // Turn on the appropriate pump
      }
      flush3.update();        // Update the stage countdown
      if (flush3.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem, currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
      }
      break;
    case 6: // Vinegar
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        vinegar.display(1);
        flush4.display(3);
        vinegar.countDown = vinegar.count;
        // Turn on the appropriate pump
        VinegarPump.ON();
      }
      vinegar.update();        // Update the stage countdown
      if (vinegar.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem, currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
        VinegarPump.OFF();
      }
      break;
    case 7: // Flush 4
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        flush4.display(1);
        phyto.display(3);
        flush4.countDown = flush4.count;
        // Turn on the appropriate pump
        Phyto_AirPump.ON();
      }
      flush4.update();        // Update the stage countdown
      if (flush4.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem, currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
      }
      break;
    case 8:// Phyto
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        phyto.display(1);
        phytoSalt.display(3);
        phyto.countDown = phyto.count;
        // Turn on the appropriate pump
        Phyto_BowFrontPump.ON();
      }
      phyto.update();        // Update the stage countdown
      if (phyto.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem, currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
        Phyto_BowFrontPump.OFF();
        Phyto_AirPump.OFF();
      }
      break;
    case 9: // Phyto Salt
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        phytoSalt.display(1);
        flush5.display(3);
        phytoSalt.countDown = phytoSalt.count;
        // Turn on the appropriate pump
        Phyto_SaltPump.ON();
      }
      phytoSalt.update();        // Update the stage countdown
      if (phytoSalt.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem, currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
        Phyto_SaltPump.OFF();
      }
      break;
    case 10: // Flush 5
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        flush5.display(1);
        CalcmPmp.display(3);
        flush5.countDown = flush5.count;
        // Turn on the appropriate pump

      }
      flush5.update();        // Update the stage countdown
      if (flush5.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
      }
      break;
    case 11: // Calcium Pump
      if (startStageFlag) {  // Initialize this stage;
        stageSetup();  // located at the end of Auto_Run_Mode.inl file
        CalcmPmp.display(1);
        frshWtr.display(3);
        CalcmPmp.countDown = CalcmPmp.count;
        // Turn on the appropriate pump
        CalciumPump.ON();
      }
      CalcmPmp.update();        // Update the stage countdown
      if (CalcmPmp.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
        CalciumPump.OFF();
      }
      break;
    case 12: // Fresh Water
      if (startStageFlag) {  // Initialize this stage;
        startStageFlag = false;
        frshWtr.display(1);
        FinalFlush.display(3);
        frshWtr.countDown = frshWtr.count;
        // Turn on the appropriate pump
        Fresh_WaterPump.ON();
      }
      frshWtr.update();        // Update the stage countdown
      if (frshWtr.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        startStageFlag = true; // Set flag for initiating the next stage.
        //  Turn off the appropriate pump
        Fresh_WaterPump.OFF();
      }
      break;
    case 13: // Final Flush
      if (startStageFlag) {  // Initialize this stage;
        stageSetup(); // located at the end of Auto_Run_Mode.inl file
        FinalFlush.display(1);
        lcd.setCursor(0,2);
        lcd.print(blankLine);
        lcd.setCursor(0,3);
        lcd.print("Last dose Bow Front");
        FinalFlush.countDown = FinalFlush.count;
        // Turn on the appropriate pump
      }
      FinalFlush.update();        // Update the stage countdown
      if (FinalFlush.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true;
        //  Turn off the appropriate pump
        Flush_BowFrontPump.OFF();
      }
      break;
    case 14: // Predator Flush 1
      if (startStageFlag) {  // Initialize this stage;
        stageSetup(); // located at the end of Auto_Run_Mode.inl file
        Predator_Flush1.display(1);
        Predator_Phyto.display(3);
        Predator_Flush1.countDown = Predator_Flush1.count;
        // Turn on the appropriate pump
        Flush_PredatorPump.ON();
        Phyto_AirPump.ON();
      }
      Predator_Flush1.update();        // Update the stage countdown
      if (Predator_Flush1.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true;
        //  Turn off the appropriate pump
        
      }
      break;
    case 15: // Predator Phyto
      if (startStageFlag) {  // Initialize this stage;
        stageSetup(); // located at the end of Auto_Run_Mode.inl file
        Predator_Phyto.display(1);
        Predator_Flush2.display(3);
        Predator_Phyto.countDown = Predator_Phyto.count;
        // Turn on the appropriate pump
        Phyto_PredatorPump.ON();
      }
      Predator_Phyto.update();        // Update the stage countdown
      if (Predator_Phyto.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true;
        //  Turn off the appropriate pump
        Phyto_PredatorPump.OFF();
        Phyto_AirPump.OFF();
      }
      break;
    case 16: // Predator Flush 2
      if (startStageFlag) {  // Initialize this stage;
        stageSetup(); // located at the end of Auto_Run_Mode.inl file
        Predator_Flush2.display(1);
        Predator_Vinegar.display(3);
        Predator_Flush2.countDown = Predator_Flush2.count;
        // Turn on the appropriate pump
      }
      Predator_Flush2.update();        // Update the stage countdown
      if (Predator_Flush2.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true;
        //  Turn off the appropriate pump
      }
      break;
    case 17: // Predator Vinegar
      if (startStageFlag) {  // Initialize this stage;
        stageSetup(); // located at the end of Auto_Run_Mode.inl file
        Predator_Vinegar.display(1);
        Predator_Flush3.display(3);
        Predator_Vinegar.countDown = Predator_Vinegar.count;
        // Turn on the appropriate pump
        Vinegar_PredatorPump.ON();
      }
      Predator_Vinegar.update();        // Update the stage countdown
      if (Predator_Vinegar.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true;
        //  Turn off the appropriate pump
        Vinegar_PredatorPump.OFF();
      }
      break;
    case 18: // Predator Flush 3
      if (startStageFlag) {  // Initialize this stage;
        stageSetup(); // located at the end of Auto_Run_Mode.inl file
        Predator_Flush3.display(1);
        Predator_Spare.display(3);
        Predator_Flush3.countDown = Predator_Flush3.count;
        // Turn on the appropriate pump
      }
      Predator_Flush3.update();        // Update the stage countdown
      if (Predator_Flush3.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true;
        //  Turn off the appropriate pump
      }
      break;
    case 19: // Predator Spare
      if (startStageFlag) {  // Initialize this stage;
        stageSetup(); // located at the end of Auto_Run_Mode.inl file
        Predator_Spare.display(1);
        Predator_Flush4.display(3);
        Predator_Spare.countDown = Predator_Spare.count;
        // Turn on the appropriate pump
        Spare_PredatorPump.ON();
        Phyto_FertPump.ON();
      }
      Predator_Spare.update();        // Update the stage countdown
      if (Predator_Spare.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true;
        //  Turn off the appropriate pump
        Spare_PredatorPump.OFF();
        Phyto_FertPump.OFF();
      }
      break;
    case 20: // Predator Flush 4
      if (startStageFlag) {  // Initialize this stage;
        stageSetup(); // located at the end of Auto_Run_Mode.inl file
        Predator_Flush4.display(1);
        lcd.setCursor(0,2);
        lcd.print(blankLine);
        lcd.setCursor(0,3);
        lcd.print("Last dose Predator");
        Predator_Flush4.countDown = Predator_Flush4.count;
        // Turn on the appropriate pump
      }
      Predator_Flush4.update();        // Update the stage countdown
      if (Predator_Flush4.complete) {  // Turn off pump and prepare for next stage.
        currentStage += 1;  //  Increment stage counter to the next stage.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        startStageFlag = true;
        //  Turn off the appropriate pump
        Flush_PredatorPump.OFF();
      }
      break;

    case 21: // Sit here and wait until time = start time.
      if (startStageFlag){// Initialize this stage
        startStageFlag = false;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dose cycle complete.");
        lcd.setCursor(0,1);
        lcd.print("Cycle Count: ");
        displayNum(cycleCounter,15,1);
        lcd.setCursor(0,2);
        lcd.print("Next cycle: ");
        if(startHr<10){lcd.print("0");}
        lcd.print(startHr);
        lcd.print(":");
        if(startMin<10){lcd.print("0");}
        lcd.print(startMin);
        lcd.print(":");
        if(startSec<10){lcd.print("0");}
        lcd.print(startSec);
        delay(1500);
        cycleCounter ++;
        displayNum(cycleCounter,15,1);
        DosEEPROM.memWrite(cycleCounterMem,cycleCounter);
      }

      lcd.setCursor(10,3);
      rtc.updateTime();
      hh = rtc.getHours();
      mm = rtc.getMinutes();
      ss = rtc.getSeconds();
      if(hh<10){lcd.print("0");}
      lcd.print(hh);
      lcd.print(":");
      if(mm<10){lcd.print("0");}
      lcd.print(mm);
      lcd.print(":");
      if(ss<10){lcd.print("0");}
      lcd.print(ss);

      if(((ss<4) && (startMin==mm)) && (startHr==hh)){
        startStageFlag = true;
        currentStage = 1;  //  Reset stage counter to the beginning to start a new cycle.
        DosEEPROM.memWrite(currentStageMem,currentStage);
        
      }
      break;
  }  // End of switch-case structure.
}  //  End of pumpUpdate() prodecure.

void stageSetup(){
  startStageFlag = false;
  lcd.setCursor(0, 0);  //Set cursor to character 0 on row
  lcd.print("Running:    ");
  displayClockTime();
}
