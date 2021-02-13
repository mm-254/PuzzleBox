//Puzzle box; Virtual/stayHome Scavenger hunt
// Could be an educational toy/scavenger hunt aid, OR a personal safe
//The user must have the key first (i.e. the RFID module) [could be hidden in a scavenger hunt scenario]
//The key activates the box, which then presents a series of clues, set in cities around the world, to the user. The clues point to numbered solutions on the surface of the box. 
//The user must enter the correct solution number using buttons to proceed to the next level
//The number is sent to python which will retrieve a video of a place and the clue from its database
//If the answer is wrong, buzzer will beep and if right, LED will display 'well done'
//After the final solution the servo will turn to unlatch the puzzle box

//Mandira Marambe

#include <Servo.h> 
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
//UID: E6 28 CB F7

Servo servo;

#define LA3 880.00
#define Q 60000/120 //quarter 1/4 
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int digit1  = 0;
int digit2  = 0;
int digit = 0;
int solution = 0;
int detect = 1;
int level = 1;
int ans1 = 04;
int ans2 = 22;
int ans3 = 66;
int key = 0;

int b1 = 7 ;
int b2 = 8 ;
int b3 = 9;
int buzzer = A1;
int LED = 3;
char array0[] = "_ _";
char array1[] = "Wrong Answer";
char array2[] = "Well Done!";
char array3[] = "Box Unlocked!";

LiquidCrystal lcd(4, 6, 10, 11, 12, 13);
//----------------------------------------------------------------------------------------------------------

void setup() {
  
 pinMode(A0, OUTPUT);//servo
 pinMode(8, INPUT_PULLUP);
 pinMode(7, INPUT_PULLUP);
 pinMode(9, INPUT_PULLUP);
 pinMode(buzzer, OUTPUT);
 Serial.begin(9600);

servo.attach(A0);
servo.write(0);
digit = 0;

SPI.begin();      // Initiate  SPI bus
mfrc522.PCD_Init();   // Initiate MFRC522

}

//----------------------------------------------------------------------------------------------------------
void loop() {

switch(digit){
  case 0:
  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print("Read Key");
  digit = checkKey();

  if (digit == 1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Puzzle 01");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.println(level);
    lcd.print("Where is Ares?");
    delay(10000);
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print(array0);
    break;
  }

  break;
  
  case 1: //digit 1

  if( digitalRead(b3)== LOW){ //+1
    digit1 = digit1+1;
    lcd.clear();
    lcd.setCursor(7,0);
    lcd.print(digit1);
    lcd.setCursor(9,0);
    lcd.print(digit2);
    delay(500);
    break;
   }
  
    if( digitalRead(b1)== LOW){//-1
    digit1 = digit1-1;
    lcd.setCursor(7,0);
    lcd.print(digit1);
    lcd.setCursor(9,0);
    lcd.print(digit2);
    delay(500);
    break;
   }
   
    if( digitalRead(b2)== LOW){//change to next digit
    digit = digit+1;
    lcd.setCursor(7,0);
    lcd.print(digit1);
    lcd.setCursor(9,0);
    lcd.print(digit2);
    delay(500);
    break;
   }
   break;
   
//--------------------------------------------------------------------------------------------------------
  case 2: //digit 2
  
    if( digitalRead(b3)== LOW){ //+1
    digit2 = digit2+1;
    lcd.setCursor(7,0);
    lcd.print(digit1);
    lcd.setCursor(9,0);
    lcd.print(digit2);
    delay(500);
    break;
   }
  
    if( digitalRead(b1)== LOW){//-1
    digit2 = digit2-1;
    lcd.setCursor(7,0);
    lcd.print(digit1);
    lcd.setCursor(9,0);
    lcd.print(digit2);
    delay(500);
    break;
   }
   
    if( digitalRead(b2)== LOW){
    digit = digit+1;
    solution = digit1*10 + digit2;
    delay(500);
    break;
   }
   break;
//---------------------------------------------------------------------------------------------------
  case 3:
   //clues
   
    if (level ==1){
      if (solution == ans1){
      level = level+1;
      digit = 1;
      digit1 = 0;
      digit2=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(array2); 
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Press Q");   
      delay(6000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Puzzle 02");
      delay(2000);
      lcd.clear();
      Serial.println(level);
      lcd.setCursor(0,1);
      lcd.print("_ _ 1B Baker St");
      delay(10000);
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print(array0);
      break;
        }
    else {
      digit = 1;
      digit1 = 0;
      digit2=0;
      tone(buzzer,LA3,Q); 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(array1);
      delay(2000);   
      servo.write(0);
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print(array0);
      delay(500);
       break;
       }
    }

      if (level ==2){
      if (solution == ans2){
      level = level+1;
      digit = 1;
      digit1 = 0;
      digit2=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(array2); 
      delay(2000);
       lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Press Q");   
      delay(6000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Puzzle 03");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      Serial.println(level);
      lcd.print("Towering Sphinx!");
      delay(10000);
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print(array0);
      break;
        }
    else {
      digit = 1;
      digit1 = 0;
      digit2=0;
      tone(buzzer,LA3,Q); 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(array1);   
      delay(2000);
      servo.write(0);
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print(array0);
      delay(500);
       break;
       }
    }

      if (level ==3){
      if (solution == ans3){
      level = 0;
      digit = 1;
      digit1 = 0;
      digit2=0;
      digitalWrite(LED, HIGH);
      servo.write(180);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(array3); 
      playTune();
      break;
        }
    else {
      digit = 1;
      digit1 = 0;
      digit2=0;
      tone(buzzer,LA3,Q); 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(array1);  
      delay(2000); 
      servo.write(0);
      lcd.clear();
      lcd.setCursor(7,0);
      lcd.print(array0);
      delay(500);
       break;
       }
    }
 break;  

}
 
}

int checkKey(){
   //Read Key
  // Look for new cards
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
  return(digit);
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
  return(digit);
  }

  //Show UID on serial monitor
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "E6 28 CB F7") //change here the UID of the card/cards that you want to give access
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Access granted");
    digit = digit+1;
    digitalWrite(LED,HIGH);
    playTune();
    digitalWrite(LED,LOW);
    delay(1000);
    return(digit);

  }
 
 else   {
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Access denied");
     tone(buzzer,LA3,Q); 
    delay(3000);
    return(digit);
  }
}


void playTune() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

  }
}
