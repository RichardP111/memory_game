/* Created by Richard Pu

Memory game for TEJ201-01|Thornhill SS

richardpu6@gmail.com
Memory Game is made possible by open source projects: https://docs.google.com/document/d/1chmq-w709f7BhciBZjUFDth4jQfBt6dHSzW_fdwIHU8/edit?usp=sharing 
Beta 1.7
*/

//defines lcd display
#include <LiquidCrystal_I2C.h> // Library for LCD  
LiquidCrystal_I2C lcd(0x27, 16, 2); //Setting up display, 0x27 display adress, 16 rows, 2 col

//defines pin numbers
const int speak = 3;
const int ledB = 4;
const int ledR = 5;
const int ledGY = 6;
const int ledG = 7;
const int swtichB = 8;
const int swtichR = 9;
const int swtichGY = 10;
const int swtichG = 2;
const int switchmain = 13;

//defines speaker
int NOTE_SUSTAIN = 300; //sets how long a note plays

//Game modes: EASY, MED, HARD, DEATH
//defines LED flash speed 
int EASYledtime = 800;
int MEDledtime = 500;
int HARDledtime = 300;
int DEATHledtime = 30;
int flashLimit = EASYledtime;

//defines time between flash speed
int EASYflashtime = 1000;
int MEDflashtime = 1000;
int HARDflashtime = 200;
int DEATHflashtime = 50;
int speedLimit = EASYflashtime;

//defines amount of time you have to press buttons
int EASYbuttontime = 5000;
int MEDbuttontime = 3000;
int HARDbuttontime = 1500;
int DEATHbuttontime = 1000;
int timeLimit = EASYbuttontime;

//defines game variables
int currentLevel = 0; //user level
int wineasyLevel = 5; //the level which easy gamemode is finished
int winLevel = 10; //the level which each gamemode is finished
int windeathlevel = 20; //the level which death mode is finished
int ledNumber = 0; //number of flashes each level, adds by one each level 
int gameBoard[100];
#define GRAY  0
#define BLUE    1
#define GREEN 2
#define RED   3
#define MAIN 10
#define noBUTTON 0  

//setup - start up
void setup(){
  noTone(speak);
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  lcd.noBlink();
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Memory Game"); //print game name
  lcd.setCursor(4, 1); //move cursor to (4, 1)
  lcd.print("Starting..."); //print booting seq 
  pinMode(speak, OUTPUT); //set speaker as output
  pinMode(ledB, OUTPUT); //set blue LED as output
  pinMode(ledR, OUTPUT); //set red LED as output
  pinMode(ledGY, OUTPUT); //set gray LED as output
  pinMode(ledG, OUTPUT);//set green LED as output
  pinMode(swtichB, INPUT);//set blue swtich as input
  pinMode(swtichR, INPUT);//set red swtich as input
  pinMode(swtichGY, INPUT);//set gray swtich as input
  pinMode(swtichG, INPUT);//set green swtich as input
  pinMode(switchmain, INPUT);//set main selection switch swtich as input
  Serial.begin(9600); //starts serial communication
  delay(2000); //delay
  lcd.clear(); //clear display
}

//main loop
void loop(){
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Select game mode"); //print main menu
  lcd.setCursor(2, 1); //move cursor to (4, 1)
  lcd.print("Hold button"); //print main menu
  delay(1500); //delay
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Game mode:"); //print main menu
  lcd.setCursor(4, 1); //move cursor to (4, 1)
  lcd.print("EASY"); //print main menu
  if (digitalRead(switchmain) == HIGH){
    easy();
  }
  delay(1500);
  if (digitalRead(switchmain) == HIGH){
    easy();
  }
  delay(1500); //delay
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Game mode:"); //print main menu
  lcd.setCursor(4, 1); //move cursor to (4, 1)
  lcd.print("MEDIUM"); //print main menu
  if (digitalRead(switchmain) == HIGH){
    med();
  }
  delay(1500);
  if (digitalRead(switchmain) == HIGH){
    med();
  }
  delay(1500); //delay
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Game mode:"); //print main menu
  lcd.setCursor(4, 1); //move cursor to (4, 1)
  lcd.print("HARD"); //print main menu
  if (digitalRead(switchmain) == HIGH){
    hard();
  }
  delay(1500);
  if (digitalRead(switchmain) == HIGH){
    hard();
  }
  delay(1500); //delay
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Game mode:"); //print main menu
  lcd.setCursor(4, 1); //move cursor to (4, 1)
  lcd.print("DEATH"); //print main menu
  if (digitalRead(switchmain) == HIGH){
    death();
  }
  delay(1500);
  if (digitalRead(switchmain) == HIGH){
    death();  
  }
  delay(1500); //delay
}

//EASY
void easy(){
  Reset();
  screencount(); //starts countdown
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("SELETED MODE:"); //print main menu
  lcd.setCursor(4, 1); //move cursor to   (0, 0)
  lcd.print("EASY"); //print main menu
  timeLimit = EASYbuttontime;
  flashLimit = EASYledtime;
  speedLimit = EASYflashtime;
  currentLevel = 0;
  randomSeed(analogRead(0));
  while (currentLevel < wineasyLevel){
    addlight();
    showlight();
    lcd.clear(); //clear display
    lcd.setCursor(0, 0); //move cursor to   (0, 0)
    lcd.print("SELETED MODE:"); //print main menu
    lcd.setCursor(4, 1); //move cursor to   (0, 0)
    lcd.print("EASY"); //print main menu
    seqDone();
    
    for (byte currentMove = 0; currentMove < currentLevel; currentMove++){
      
      byte choice = buttonSelect();
      if (choice == 0){
        losegame();
        playlosetone();
        Serial.println("Game lost");
        return;
      }
      if (choice == MAIN){
        sound();
        exit();
        return;
      }
      if (choice != gameBoard[currentMove]){
        losegame();
        playlosetone();
        Serial.println("Game lost");
        return;
      }
      sound();
      delay(speedLimit);
    }
    playwintone();
  }
  wingame();
  Serial.println("Game won");
  return;
}
//MED
void med(){
  Reset();
  screencount();
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("SELETED MODE:"); //print main menu
  lcd.setCursor(4, 1); //move cursor to   (0, 0)
  lcd.print("MEDIUM"); //print main menu
  timeLimit = MEDbuttontime;
  flashLimit = MEDledtime;
  speedLimit = MEDflashtime;
  currentLevel = 0;
  randomSeed(analogRead(0));
  while (currentLevel < winLevel){
    addlight();
    showlight();
    lcd.clear(); //clear display
    lcd.setCursor(0, 0); //move cursor to   (0, 0)
    lcd.print("SELETED MODE:"); //print main menu
    lcd.setCursor(4, 1); //move cursor to   (0, 0)
    lcd.print("MEDIUM"); //print main menu
    seqDone();
    
    for (byte currentMove = 0; currentMove < currentLevel; currentMove++){
      
      byte choice = buttonSelect();
      if (choice == 0){
        losegame();
        playlosetone();
        Serial.println("Game lost");
        return;
      }
      if (choice == MAIN){
        sound();
        exit();
        return;
      }
      if (choice != gameBoard[currentMove]){
        losegame();
        playlosetone();
        Serial.println("Game lost");
        return;
      }
      sound();
      delay(speedLimit);
    }
    playwintone();
  }
  wingame();
  Serial.println("Game won");
  return;
}

//HARD
void hard(){
  Reset();
  screencount();
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("SELETED MODE:"); //print main menu
  lcd.setCursor(4, 1); //move cursor to   (0, 0)
  lcd.print("HARD"); //print main menu
  timeLimit = HARDbuttontime;
  flashLimit = HARDledtime;
  speedLimit = HARDflashtime;
  currentLevel = 0;
  randomSeed(analogRead(0));
  while (currentLevel < windeathlevel){
    addlight();
    showlight();
    lcd.clear(); //clear display
    lcd.setCursor(0, 0); //move cursor to   (0, 0)
    lcd.print("SELETED MODE:"); //print main menu
    lcd.setCursor(4, 1); //move cursor to   (0, 0)
    lcd.print("HARD"); //print main menu
    seqDone();
    
    for (byte currentMove = 0; currentMove < currentLevel; currentMove++){
      
      byte choice = buttonSelect();
      if (choice == 0){
        losegame();
        playlosetone();
        Serial.println("Game lost");
        return;
      }
      if (choice == MAIN){
        sound();
        exit();
        return;
      }
      if (choice != gameBoard[currentMove]){
        losegame();
        playlosetone();
        Serial.println("Game lost");
        return;
      }
      sound();
      delay(speedLimit);
    }
    playwintone();
  }
  wingame();
  Serial.println("Game won");
  return;
}
//DEATH
void death(){
  Reset();
  screencount();
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("SELETED MODE:"); //print main menu
  lcd.setCursor(2, 1); //move cursor to   (0, 0)
  lcd.print("DEATH MODE"); //print main menu
  timeLimit = DEATHbuttontime;
  flashLimit = DEATHledtime;
  speedLimit = DEATHflashtime;
  currentLevel = 0;
  randomSeed(analogRead(0));
  while (currentLevel < windeathlevel){
    addlight();
    showlight();
    lcd.clear(); //clear display
    lcd.setCursor(0, 0); //move cursor to   (0, 0)
    lcd.print("SELETED MODE:"); //print main menu
    lcd.setCursor(4, 1); //move cursor to   (0, 0)
    lcd.print("DEATH"); //print main menu
    seqDone();
    
    
    for (byte currentMove = 0; currentMove < currentLevel; currentMove++){
      byte choice = buttonSelect();
      if (choice == 0){
        losegame();
        playlosetone();
        Serial.println("Game lost");
        return;
      }
      if (choice == MAIN){
        sound();
        exit();
        return;
      }
      if (choice != gameBoard[currentMove]){
        losegame();
        playlosetone();
        Serial.println("Game lost");
        return;
      }
      sound();
      delay(speedLimit);
    }
    playwintone();
  }
  windeathgame();
  Serial.println("Game won");
  return;
}

//buzzer win sound
void playwintone(){
  tone(speak,440.00);
  delay(500);
  tone(speak,523.25);
  delay(400);
  tone(speak,783.99);
  delay(600);
  noTone(speak);
}

//buzzer lose sound
void playlosetone(){
  tone(speak,293.66);
  delay(500);
  tone(speak,164.81);
  delay(700);
  noTone(speak);
}

//buzzer light done sound
void seqDone(){
  tone(speak,600);
  delay(300);
  noTone(speak);
}

//buzzer mode win sound
void playmodetone(){
  tone(speak,880.00);
  delay(NOTE_SUSTAIN);
  tone(speak,987.77);
  delay(NOTE_SUSTAIN);
  tone(speak,523.25);
  delay(NOTE_SUSTAIN);
  tone(speak,987.77);
  delay(NOTE_SUSTAIN);
  tone(speak,523.25);
  delay(NOTE_SUSTAIN);
  tone(speak,587.33);
  delay(NOTE_SUSTAIN);
  tone(speak,523.25);
  delay(NOTE_SUSTAIN);
  tone(speak,587.33);
  delay(NOTE_SUSTAIN);
  tone(speak,659.25);
  delay(NOTE_SUSTAIN);
  tone(speak,587.33);
  delay(NOTE_SUSTAIN);
  tone(speak,659.25);
  delay(NOTE_SUSTAIN);
  tone(speak,659.25);
  delay(NOTE_SUSTAIN);
  noTone(speak);
}

//BETA: death win song
int wish_melody[] = {
  246.94, 
  349.23, 349.23, 392.00, 349.23, 329.63,

  293.66, 293.66, 293.66,
  392.00, 392.00, 440.00, 392.00, 349.23,

  329.63, 329.63, 329.63,
  440.00, 440.00, 493.88, 440.00, 392.00,

  349.23, 293.66, 246.94, 246.94,
  293.66, 392.00, 329.63,
  349.23
};

int
  wish_tempo[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};

//buzzer death win sound
void playwindeathtone(){
  int size = sizeof(wish_melody) / sizeof(int);
  Serial.println("WIN DEATH MUSIC");
  for (int thisNote = 0; thisNote < size; thisNote++) {
    Serial.println("test");
    int noteDuration = 1000 / wish_tempo[thisNote];
    buzz(speak, wish_melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    buzz(speak,0, noteDuration);
  }
}
 
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2;
  long numCycles = frequency * length / 1000;
  for (long i = 0; i < numCycles; i++) {
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin, LOW);
    delayMicroseconds(delayValue);
  }
}

//count down for game to start
void screencount(){
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Starting in"); //print main menu
  lcd.setCursor(4, 1); //move cursor to (4, 1)
  lcd.print("3"); //print main menu
  delay(1000); //delay
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Starting in"); //print main menu
  lcd.setCursor(4, 1); //move cursor to (4, 1)
  lcd.print("2"); //print main menu
  delay(1000); //delay
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Starting in"); //print main menu
  lcd.setCursor(4, 1); //move cursor to (4, 1)
  lcd.print("1"); //print main menu
  delay(1000); //delay
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("START"); //print main menu
  delay(1000); //delay
  Serial.println("Game STARTED");
}

//plays sound click of button and when done
void sound(){
  tone(speak,880.00);
  delay(100);
  noTone(speak);
}

//resets all values
void Reset(){
  int gameMode = 0;
  int timeLimit = EASYbuttontime;
  int flashLimit = EASYledtime;
  int speedLimit = EASYflashtime;
  int currentLevel = 0; //user level
  int ledNumber = 0; //number of flashes each level, adds by one each level 
  int currentMove = 0;
  int choice = 10;
  for (int i = 0; i < 100; i++) {
    gameBoard[i] = 9;
  }
  #define GRAY  (1 << 0)
  #define BLUE    (1 << 1)
  #define GREEN (1 << 2)
  #define RED   (1 << 3)
  #define noBUTTON 0  
  Serial.println("All values have been reset");
}

//win
void wingame(){
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("You won"); //print main menu
  lcd.setCursor(4, 1); //move cursor to   (0, 0)
  lcd.print("Congrats"); //print main menu
  playmodetone();
  delay(2000); //delay
}
  
//win death
void windeathgame(){
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("u hacking"); //print main menu
  lcd.setCursor(2, 1); //move cursor to   (0, 0)
  lcd.print("911 is coming"); //print main menu
  playwindeathtone();
  delay(2000); //delay
}
    
//lose
void losegame(){
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("You lose"); //print main menu
  lcd.setCursor(4, 1); //move cursor to   (0, 0)
  lcd.print("Try again"); //print main menu
  delay(2000); //delay
}

//time out
void timeout(){
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("TIMEOUT"); //print main menu
  delay(2000); //delay
}

//exit
void exit(){
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Exiting..."); //print main menu
  delay(1000); //delay
}
  
//adds a light every level
void addlight(){
  byte newLight = random(0, 4);
  Serial.println(newLight);

  if(newLight == 0) {
    newLight = GRAY;
  }else if (newLight == 1) {
    newLight = BLUE;
  }else if (newLight == 2)  {
    newLight = GREEN;
  }else if (newLight == 3) {
    newLight = RED;
  }
  
  gameBoard[currentLevel++] = newLight;    
  

  Serial.println("Current Level: " + String(currentLevel));
  Serial.println("Game Board: ");
  for (int i = 0; i < currentLevel; i++) {
    Serial.print(gameBoard[i]);
    Serial.print(" ");
  }
  lcd.clear(); //clear display
  lcd.setCursor(0, 0); //move cursor to   (0, 0)
  lcd.print("Current Level:"); //print main menu
  lcd.setCursor(5, 1); //move cursor to   (0, 0)
  lcd.print(currentLevel); //print main menu
}

//play back seq
void showlight(){
  for (byte currentMove = 0 ; currentMove < currentLevel ; currentMove++) {
    flashLED(gameBoard[currentMove]);
    delay(150); 
  }
}

//lights light up
void flashLED(byte led){
  if ((led & GRAY) != 0){
    digitalWrite(ledGY, HIGH);
    delay(flashLimit);
    digitalWrite(ledGY, LOW);
  }else{
    digitalWrite(ledGY, LOW);
  }
  
  if ((led & BLUE) != 0){
    digitalWrite(ledB, HIGH);
    delay(flashLimit);
    digitalWrite(ledB, LOW);
  }else{
    digitalWrite(ledB, LOW);
  }
  
  if ((led & GREEN) != 0){
    digitalWrite(ledG, HIGH);
    delay(flashLimit);
    digitalWrite(ledG, LOW);
  }else{
    digitalWrite(ledG, LOW);
  }

  if ((led & RED) != 0){
    digitalWrite(ledR, HIGH);
    delay(flashLimit);
    digitalWrite(ledR, LOW);
  }else{
    digitalWrite(ledR, LOW);
  }
}

//player select button
byte buttonSelect(){
  long startTime = millis();
  
  while ((millis() - startTime) < timeLimit){
    byte button = checkPress();

    if (button != noBUTTON){ 
      while(checkPress() != noBUTTON);  
      delay(10); 
      return button;
    }
  }
  timeout();
}

//check what button has been pressed
byte checkPress(){
  if(digitalRead(swtichGY) == 1){
    sound();
    return (GRAY); 
  }else if (digitalRead(swtichB) == 1) {
    sound();
    return (BLUE); 
  }else if (digitalRead(swtichG) == 1) {
    sound();
    return (GREEN); 
  }else if (digitalRead(swtichR) == 1) {
    sound();
    return (RED); 
  }else if (digitalRead(switchmain) == 1) {
    return (MAIN);
  }
  return (noBUTTON);
}