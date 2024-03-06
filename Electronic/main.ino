#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>

int seconds = 0;
int pos = 0;

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
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

void setup()
{
  Serial.begin(9600);

  servo_3.attach(3);
  servo_5.attach(5);
  servo_10.attach(10);
  servo_11.attach(11);

  lcd_1.begin(16, 2);
  lcd_1.print("MedMachine");
  lcd_1.setBacklight(1);
}

void medOut(string servo_name)
{
  lcd_1.setCursor(0, 1);
      lcd_1.print("Processing");
      servo_name.write(100);
      delay(1000);
      servo_name.write(93);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Your welcome");
      delay(1000);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Pick a medicine");
}
void loop()
{
  char key = keypad.getKey(); // Get the pressed key

  if (key != NO_KEY)
  {
    Serial.println(key);
    lcd_1.setCursor(0, 1);
    lcd_1.print("                ");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Pressed ");
    lcd_1.print(key);
    delay(500);
    switch (key)
    {
    case 'A':
      // Action for key A
      lcd_1.setCursor(0, 1);
      lcd_1.print("Medicine A");
      delay(500);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Processing");
      servo_3.write(100);
      delay(1000);
      servo_3.write(93);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Your welcome");
      delay(1000);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Pick a medicine");
      break;

    case 'B':
      // Action for key B
      lcd_1.setCursor(0, 1);
      lcd_1.print("Medicine B");
      delay(500);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Processing");
      servo_5.write(100);
      delay(1000);
      servo_5.write(93);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Your welcome");
      delay(1000);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Pick a medicine");
      break;

    case 'C':
      // Action for key C
      lcd_1.setCursor(0, 1);
      lcd_1.print("Medicine C");
      delay(500);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Processing");
      servo_10.write(100);
      delay(1000);
      servo_10.write(93);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Your welcome");
      delay(1000);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Pick a medicine");
      break;

    case 'D':
      // Action for key D
      lcd_1.setCursor(0, 1);
      lcd_1.print("Medicine D");
      delay(500);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Processing");
      servo_11.write(100);
      delay(1000);
      servo_11.write(93);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Your welcome");
      delay(1000);
      lcd_1.setCursor(0, 1);
      lcd_1.print("Pick a medicine");
      break;

    case '1':
      // Action for key 1
      break;

    case '2':
      // Action for key 2
      break;

    case '3':
      // Action for key 3
      break;

    case '4':
      // Action for key 4
      break;

    case '5':
      // Action for key 5
      break;

    case '6':
      // Action for key 6
      break;

    case '7':
      // Action for key 7
      break;

    case '8':
      // Action for key 8
      break;

    case '9':
      // Action for key 9
      break;

    case '0':
      // Action for key 0
      break;

    case '*':
      // Action for key *
      break;

    case '#':
      // Action for key #
      break;

    default:
      // Default action
      break;
    }
  }
}
