#include <Keypad.h>
#include <LiquidCrystal.h>

// LCD setup
LiquidCrystal lcd(7,6,5,4,3,2);

// Relay lock pin
int relayPin = 8;

// Buzzer pin
int buzzer = 13;

// Password
String password = "1234";
String input = "";

// Attempt counter
int attempts = 0;
int maxAttempts = 3;

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = {9,10,11,12};
byte colPins[COLS] = {A0,A1,A2,A3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------- SETUP ----------
void setup()
{
pinMode(relayPin, OUTPUT);
pinMode(buzzer, OUTPUT);

digitalWrite(relayPin, HIGH);

lcd.begin(16,2);

lcd.print("SMART DELIVERY");
delay(2000);

lcd.clear();
lcd.print("Enter Password");
}

// ---------- MAIN LOOP ----------
void loop()
{
char key = keypad.getKey();

if(key)
{

// CLEAR BUTTON
if(key == '*')
{
input="";
lcd.clear();
lcd.print("Input Cleared");
delay(1000);
lcd.clear();
lcd.print("Enter Password");
}

// ENTER BUTTON
else if(key == '#')
{
checkPassword();
}

// NORMAL NUMBER INPUT
else
{
input += key;
lcd.setCursor(0,1);
lcd.print(input);
}

}

}

// ---------- PASSWORD CHECK ----------
void checkPassword()
{

if(input == password)
{

lcd.clear();
lcd.print("Access Granted");

digitalWrite(relayPin, LOW);

tone(buzzer,1000,200);

delay(5000);

digitalWrite(relayPin, HIGH);

lcd.clear();
lcd.print("Box Locked");

delay(2000);

attempts = 0;

}

else
{

attempts++;

lcd.clear();
lcd.print("Wrong Password");

tone(buzzer,500,1000);

delay(2000);

if(attempts >= maxAttempts)
{

lockSystem();

}

}

input="";

lcd.clear();
lcd.print("Enter Password");

}

// ---------- SECURITY LOCK ----------
void lockSystem()
{

lcd.clear();
lcd.print("SYSTEM LOCKED");

for(int i=0;i<10;i++)
{

tone(buzzer,800);
delay(300);
noTone(buzzer);
delay(300);

}

delay(5000);

attempts=0;

lcd.clear();
lcd.print("Enter Password");

}
