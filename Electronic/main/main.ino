#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
#include <SoftwareSerial.h>



SoftwareSerial mySerial(3,2);

char incomingByte;
String incomingData;
bool atCommand = true;

int index = 0;
String number = "";
String message = "";

int seconds = 0;
int pos = 0;



const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {{'1', '2', '3', 'A'},
                        {'4', '5', '6', 'B'},
                        {'7', '8', '9', 'C'},
                        {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {0, 12, 2, 4};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo servo_3;
Servo servo_5;
Servo servo_10;
Servo servo_11;

Adafruit_LiquidCrystal lcd_1(0);

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  servo_3.attach(3);
  servo_5.attach(5);
  servo_10.attach(10);
  servo_11.attach(11);
  lcd_1.begin(16, 2);
  lcd_1.print("MedMachine");
  lcd_1.setBacklight(1);
  while (!mySerial.available()) {
    mySerial.println("AT");
    delay(1000);
    Serial.println("connecting....");
  }

  Serial.println("Connected..");

  mySerial.println("AT+CMGF=1");  //Set SMS Text Mode
  delay(1000);
  mySerial.println("AT+CNMI=1,2,0,0,0");  //procedure, how to receive messages from the network
  delay(1000);
  mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read unread messages

  Serial.println("Ready to received Commands..");
}

void loop() {
  if (mySerial.available()) {
    delay(100);

    // Serial buffer
    while (mySerial.available()) {
      incomingByte = mySerial.read();
      incomingData += incomingByte;
    }

    delay(10);
    if (atCommand == false) {
      receivedMessage(incomingData);
    } else {
      atCommand = false;
    }

    //delete messages to save memory
    if (incomingData.indexOf("OK") == -1) {
      mySerial.println("AT+CMGDA=\"DEL ALL\"");
      delay(1000);
      atCommand = true;
    }

    incomingData = "";
  }
}

void switchMedicine(char key) {
  switch (key) {
    case 'A':
      processMedicine(servo_3);
      break;
    case 'B':
      processMedicine(servo_5);
      break;
    case 'C':
      processMedicine(servo_10);
      break;
    case 'D':
      processMedicine(servo_11);
      break;
    default:
      break;
  }
}

void processMedicine(Servo& servo) {
  lcd_1.setCursor(0, 1);
  lcd_1.print("Processing");
  servo.write(100);
  delay(1000);
  servo.write(93);
  lcd_1.setCursor(0, 1);
  lcd_1.print("Your welcome");
  delay(1000);
  lcd_1.setCursor(0, 1);
  lcd_1.print("Pick a medicine");
}

void receivedMessage(String inputString) {

  //Get The number of the sender
  index = inputString.indexOf('"') + 1;
  inputString = inputString.substring(index);
  index = inputString.indexOf('"');
  number = inputString.substring(0, index);
  Serial.println("Number: " + number);

  //Get The Message of the sender
  index = inputString.indexOf("\n") + 1;
  message = inputString.substring(index);
  message.trim();
  Serial.println("Message: " + message);
  message.toUpperCase(); // uppercase the message received


  //turn Device 1 ON
  if (message.indexOf("A") > -1) {
    processMedicine(servo_3);
    delay(1000);
    Serial.println("Medicine A");
  }

  //turn Device 1 OFF
  if (message.indexOf("B") > -1) {
    processMedicine(servo_5);
    Serial.println("Medicine B");
  }

  //turn Device 2 ON
  if (message.indexOf("C") > -1) {
    processMedicine(servo_10);
    delay(1000);
    Serial.println("Medicine C");
  }

  //turn Device 2 OFF
  if (message.indexOf("D") > -1) {
    processMedicine(servo_11);
    Serial.println("Medicine D");
  }

  delay(50);// Added delay between two readings
}