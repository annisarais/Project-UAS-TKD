#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> // Library komunikasi I2C 
#include <LiquidCrystal_I2C.h> // Library modul I2C LCD
#define RST_PIN   9     // Configurable, see typical pin layout above
#define SS_PIN    10    // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 
const int kuning = 8;
const int merah = 7;

/* Set your new UID here */
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}

MFRC522::MIFARE_Key key;
Servo myservo;  
void setup() {
  myservo.attach(3);  // servo terhubung pin 3
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  pinMode (8, OUTPUT);
  pinMode (7, OUTPUT);
  // inisialisasi LCD:
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("TEMPELKAN KARTU"); 
  lcd.setCursor(0, 1); 
  lcd.print("E-TOLL ANDA");
  delay(1000);
}
 
void loop() {
  myservo.write(170); 
  delay(2000); 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "07 56 14 D8") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite (8, HIGH);
    delay(100);
    digitalWrite (8, LOW);
    delay(100);
    digitalWrite (8, HIGH);
    delay(100);
    digitalWrite (8, LOW);
    delay(100);
    lcd.clear();
    lcd.print("SELAMAT JALAN"); 
    lcd.setCursor(0, 1); 
    lcd.print("STAY SAFE :) ;)");
    delay(2000);
  myservo.write(30); 
  delay(2000);
    delay(3000);
      lcd.clear();
  lcd.print("TEMPELKAN KARTU"); 
  lcd.setCursor(0, 1); 
  lcd.print("E-TOLL ANDA");
  delay(1000);
  }
 
 else   {
    Serial.println(" Access denied");
    Serial.println();
    digitalWrite (7, HIGH);
    delay(100);
    digitalWrite (7, LOW);
    delay(100);
    digitalWrite (7, HIGH);
    delay(100);
    digitalWrite (7, LOW);
    delay(100);
    lcd.clear();
    lcd.print("AKSES DITOLAK"); 
    lcd.setCursor(0, 1); 
    lcd.print("KARTU INVALID");
    delay(2000);
  myservo.write(170); 
  delay(2000); 
    delay(3000);
    lcd.clear();
  lcd.print("TEMPELKAN KARTU"); 
  lcd.setCursor(0, 1); 
  lcd.print("E-TOLL ANDA");
  delay(1000);
  }
} 
