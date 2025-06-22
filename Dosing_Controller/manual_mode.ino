void manualMode(){
  if(oldMode != 3){
    oldMode = 3;
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Manual Mode");
    lcd.setCursor(0,1);
    lcd.print("Use knob to select a");
    lcd.setCursor(0,2);
    lcd.print("pump; use buttons to");
    lcd.setCursor(0,3);
    lcd.print("start and stop pump.");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,3);
    lcd.print("START           STOP");
    encoderCount = 1;
  }

byte d = SpareIO.MCPRead(GPIO); // Read the the pushbutton port.
bool lft = bitRead(d,pbLeft);
bool cent = bitRead(d,pbCenter);
bool rite = bitRead(d,pbRight);

if(encoderCount>16){encoderCount=1;}
if(encoderCount<1){encoderCount=16;}

lcd.setCursor(0,0);
switch(encoderCount){
  case 1:  // Fresh Water Pump connected to output 0
    lcd.print("Fresh Water Pump   0");
    lcd.setCursor(3,1);
    if(lft){ Fresh_WaterPump.ON();}// "START" pushbutton is depressed
    if(rite){ Fresh_WaterPump.OFF();}// "STOP" pushbutton is depressed
    if(Fresh_WaterPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;
  case 2:  // Soda Pump connected to output 1
    lcd.print("Soda Pump          1");
    lcd.setCursor(3,1);
    if(lft){SodaPump.ON();}// "START" pushbutton is depressed
    if(rite){SodaPump.OFF();}// "STOP" pushbutton is depressed
    if(SodaPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 3:  // Part C Pump connected to output 2
    lcd.print("Part C Pump        2");
    lcd.setCursor(3,1);
    if(lft){PartCPump.ON();}// "START" pushbutton is depressed
    if(rite){PartCPump.OFF();}// "STOP" pushbutton is depressed
    if(PartCPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 4:  // Calcium Pump connected to output 3
    lcd.print("Calcium Pump       3");
    lcd.setCursor(3,1);
    if(lft){CalciumPump.ON();}// "START" pushbutton is depressed
    if(rite){CalciumPump.OFF();}// "STOP" pushbutton is depressed
    if(CalciumPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 5:  // Phyto Bowfront Pump connected to output 4
    lcd.print("Phyto Bowfront Pmp 4");
    lcd.setCursor(3,1);
    if(lft){Phyto_BowFrontPump.ON();}// "START" pushbutton is depressed
    if(rite){Phyto_BowFrontPump.OFF();}// "STOP" pushbutton is depressed
    if(Phyto_BowFrontPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 6:  // Phyto Fertilizer front Pump connected to output 5
    lcd.print("Phyto Fertilzr Pmp 5");
    lcd.setCursor(3,1);
    if(lft){Phyto_FertPump.ON();}// "START" pushbutton is depressed
    if(rite){Phyto_FertPump.OFF();}// "STOP" pushbutton is depressed
    if(Phyto_FertPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 7:  // Phyto Salt Pump connected to output 6
    lcd.print("Phyto Salt Pump    6");
    lcd.setCursor(3,1);
    if(lft){Phyto_SaltPump.ON();}// "START" pushbutton is depressed
    if(rite){Phyto_SaltPump.OFF();}// "STOP" pushbutton is depressed
    if(Phyto_SaltPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 8:  // Phyto Air Pump connected to output 7
    lcd.print("Phyto Air Pump     7");
    lcd.setCursor(3,1);
    if(lft){Phyto_AirPump.ON();}// "START" pushbutton is depressed
    if(rite){Phyto_AirPump.OFF();}// "STOP" pushbutton is depressed
    if(Phyto_AirPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 9:  // Vinegar Pump connected to output 8
    lcd.print("Vinegar Pump       8");
    lcd.setCursor(3,1);
    if(lft){VinegarPump.ON();}// "START" pushbutton is depressed
    if(rite){VinegarPump.OFF();}// "STOP" pushbutton is depressed
    if(VinegarPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 10:  // Phyto Predator Pump connected to output 9
    lcd.print("Phyto Predator Pmp 9");
    lcd.setCursor(3,1);
    if(lft){Phyto_PredatorPump.ON();}// "START" pushbutton is depressed
    if(rite){Phyto_PredatorPump.OFF();}// "STOP" pushbutton is depressed
    if(VinegarPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 11:  // Flush Bowfront Pump connected to output 10
    lcd.print("Flush Bowfrnt Pmp 10");
    lcd.setCursor(3,1);
    if(lft){Flush_BowFrontPump.ON();}// "START" pushbutton is depressed
    if(rite){Flush_BowFrontPump.OFF();}// "STOP" pushbutton is depressed
    if(Flush_BowFrontPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 12:  // Flush Predator Pump connected to output 11
    lcd.print("Flush Predatr Pmp 11");
    lcd.setCursor(3,1);
    if(lft){Flush_PredatorPump.ON();}// "START" pushbutton is depressed
    if(rite){Flush_PredatorPump.OFF();}// "STOP" pushbutton is depressed
    if(Flush_PredatorPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 13:  // Vinegar Predator Pump connected to output 12
    lcd.print("Vinegr Predatr Pmp12");
    lcd.setCursor(3,1);
    if(lft){Vinegar_PredatorPump.ON();}// "START" pushbutton is depressed
    if(rite){Vinegar_PredatorPump.OFF();}// "STOP" pushbutton is depressed
    if(Vinegar_PredatorPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 14:  // Vinegar Predator Pump connected to output 13
    lcd.print("Spare Predatr Pmp 13");
    lcd.setCursor(3,1);
    if(lft){Spare_PredatorPump.ON();}// "START" pushbutton is depressed
    if(rite){Spare_PredatorPump.OFF();}// "STOP" pushbutton is depressed
    if(Spare_PredatorPump.state){lcd.print("RUNNING");}
    else{lcd.print("STOPPED ");}
    break;  
  case 15:  // Vinegar Predator Pump connected to output 14
    lcd.print("Unused Output 14");
    lcd.setCursor(3,1);
    if(lft){
      Dosing2.PinON(GPIO,0b01000000);}// "START" pushbutton is depressed
    if(rite){
      Dosing2.PinOFF(GPIO,0b01000000);}// "START" pushbutton is depressed
    if(Dosing2.PinRead(GPIO,0b01000000)){lcd.print("RUNNING");}
    else{lcd.print("STOPPED");}
    break;  
  case 16:  // Vinegar Predator Pump connected to output 15
    lcd.print("Unused Output 15");
    lcd.setCursor(3,1);
    if(lft){
      Dosing2.PinON(GPIO,0b10000000);}// "START" pushbutton is depressed
    if(rite){
      Dosing2.PinOFF(GPIO,0b10000000);}// "STOP" pushbutton is depressed
    if(Dosing2.PinRead(GPIO,0b10000000)){lcd.print("RUNNING");}
    else{lcd.print("STOPPED");}
    break;
}

}
