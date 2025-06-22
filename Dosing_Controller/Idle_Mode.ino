// This mode will only be selected when a transient in the selector switch occurs.
void idleMode(){
  if(oldMode != 0){
    oldMode = 0;
    lcd.clear();
    lcd.setCursor(3,1);
    lcd.print("wait a sec");
    delay(1000);
  }
  lcd.setCursor(2,2);
  lcd.print(" move sel switch ");


  //byte m=98;
  //DosEEPROM.memWrite(20, m);

  byte k = DosEEPROM.memReadByte(20);
  lcd.setCursor(2,2);
  lcd.print(k);

  //int n=5258;
  //DosEEPROM.memWrite(24, n);

  int p = DosEEPROM.memReadInt(24);
  lcd.setCursor(10,2);
  lcd.print(p);

  //bool Jim = false;
  //DosEEPROM.memWrite(28,Jim);

  bool h = DosEEPROM.memReadBool(28);
  lcd.setCursor(10,1);
  lcd.print(h);

  displayNum(encoderCount,0,3);

} // End of idleMode() function.
