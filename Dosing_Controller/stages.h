
//////////////////////////////////
//  "STAGE" Class
////////////////////////////////////

//  Dosing pumps will be controlled by sequencing through a series of stages.  
//  The controls for each stage are defined within the class "stage".
//  The calling program will step through each stage.
//  The calling program will intiate the actions required by a given state; the class
//  only provides the controls for the stage, not the actions of the state.

class Stage{
  public:
  byte stageNumb, nextStage;
  String stageName;  // The name of the stage.
  bool started=false, running=false, complete=false;
  int count, countDown; // Will count down to zero to end the stage
  int memBase;

  // class constructor
  Stage(byte number, String name, int ct, int mem){
    stageNumb = number;
    stageName = name;
    count = ct;
    //countDown  = ct;
    memBase = mem;
  } // End of class constructor

  void update(){
    stageDisplayNum(countDown, 15, 1);
    countDown = countDown-1;
    if (countDown == 0){complete=true;}else{complete=false;}
  } // End of upDate method

  void display(byte row){ //  Display stage information on a prescribed row.
    lcd.setCursor(0,row);   //Set cursor to character 0 on line 1
    lcd.print("                    "); // Clear the row.
    lcd.setCursor(0,row);   //Set cursor to character 0 on line 1
    lcd.print("Stg ");
    if (stageNumb < 10){
      lcd.print(" ");
      lcd.print(stageNumb);} 
    else {lcd.print(stageNumb);}
    lcd.setCursor(7,row);   //Set cursor to character 3 on line 1
    lcd.print(stageName);
    lcd.setCursor(17,row);
    if (count < 10){
      lcd.print("  ");
      lcd.print(count);} 
    else if (count < 100){
      lcd.print(" ");
      lcd.print(count);} 
    else {lcd.print(count);}
    delay(100);
}  // End of "display()" method.

  void stageDisplayNum(int number, byte col, byte row){ // This routine add blanks to three digit numbers that are less than 10 or less than 100.
    lcd.setCursor(col,row);   //Set cursor to character location passed to the procedure
    if(number < 10){
      lcd.print("    ");
      lcd.print(number);} 
    else if (number < 100){
      lcd.print("   ");
      lcd.print(number);} 
    else if (number < 1000){
      lcd.print("  ");
      lcd.print(number);} 
    else if (number < 10000){
      lcd.print(" ");
      lcd.print(number);} 
    else {lcd.print(number);}
  }  //  End of displayNum() method.

}; //  End of "Stage" class definition.
