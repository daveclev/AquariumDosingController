void manualMode(){
  if(oldMode != 3){
    oldMode = 3;
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Manual Mode");
    lcd.setCursor(0,2);
    lcd.print("Pumps can be controlled");
    lcd.setCursor(0,3);
    lcd.print(" manually.");
    delay(1500);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print(" Manual ");
  }
lcd.setCursor(4,1);
lcd.print(encoderCount);

byte d = SpareIO.MCPRead(GPIO); // Read the the pushbutton port.
bool lft = bitRead(d,pbLeft);
bool cent = bitRead(d,pbCenter);
bool rite = bitRead(d,pbRight);
lcd.setCursor(2,3);
lcd.print(lft);
lcd.setCursor(10,3);
lcd.print(cent);
lcd.setCursor(17,3);
lcd.print(rite);
lcd.setCursor(15,2);
if(d<10){lcd.print("  ");lcd.print(d);}
else if(d<100){lcd.print(" ");lcd.print(d);}
else{lcd.print(d);}


if(lft){
  encoderCount ++;
  lcd.setCursor(4,1);
  lcd.print(encoderCount);
  while(lft){
    byte d = SpareIO.MCPRead(GPIO); // Read the the pushbutton port.
    lft =bitRead(d,pbLeft);
  }
}
}
