


//servo motor
#include <Servo.h>
//servo motor

//keypad
#include <Key.h>
#include <Keypad.h>
//keypad





//dht11 sensor
#include <DHT.h>
#include <DHT_U.h>
//servo motor
#include <Servo.h>
//servo motor

//keypad
#include <Key.h>
#include <Keypad.h>
//keypad





//dht11 sensor
#include <DHT.h>
#include <DHT_U.h>
//dht11 sensor

#include <Servo.h>
#include <Key.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo servoMotor;

char enteredCode[5];
int codeIndex = 0;
bool correctPINEntered = false;

const int motionPin = A0;
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

void setup() {
  servoMotor.write(0);
  pinMode(motionPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  servoMotor.attach(2);
  pinMode(2, OUTPUT);
  Serial.println("Enter PIN: ****");
}

void loop() {
  if (!correctPINEntered) {
    char key = keypad.getKey();
    if (key) {
      if (key == '#') {
        enteredCode[codeIndex] = '\0';
        codeIndex = 0;
        Serial.println();

        if (strcmp(enteredCode, "5255") == 0) {
          Serial.println("Correct PIN.");
          correctPINEntered = true;
          unlock();
        } else {
          Serial.print("Incorrect PIN: ");
          for (int i = 0; i < 4; i++) {
            Serial.print(enteredCode[i]);
          }
          Serial.println();
        }

        delay(1000);
        clearEnteredCode();
        Serial.println("Enter PIN: ****");
      } else if (key >= '0' && key <= '9' && codeIndex < 4) {
        enteredCode[codeIndex++] = key;
        Serial.print('*');
      }
    }
  } else {
    int motionState = digitalRead(motionPin);

    if (motionState == HIGH) {
      //delay(2000);
      Serial.println("Motion detected!");
      setColor(255, 0, 0);
      delay(1000);
      setColor(0, 255, 0);
      delay(1000);
      setColor(0, 0, 255);
      delay(1000);
      setColor(255, 255, 0);
      delay(1000);
      setColor(0, 255, 255);
      delay(1000);
      setColor(255, 0, 255);
      delay(1000);
      setColor(0, 0, 0);
      delay(2000);
    } else {
      Serial.println("No motion detected.");
    }

    //correctPINEntered = false;
    //Serial.println("Enter PIN: ****");
  }


  
}

void unlock() {
  servoMotor.write(0);
  delay(2000);
  servoMotor.write(180);
  delay(2000);
  servoMotor.write(0);
}

void clearEnteredCode() {
  for (int i = 0; i < 5; i++) {
    enteredCode[i] = '\0';
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}