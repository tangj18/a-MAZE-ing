#include <Servo.h>

#include <SoftwareSerial.h>


Servo xmotor;
Servo ymotor;
int finish = 2;
int lose = 3;

SoftwareSerial HC12(6, 7); // HC-12 TX Pin, HC-12 RX Pin

int x = 0;
int y = 0;
String xvalString = "0";
String yvalString = "0";
String buttonString = "0";
String strArr[2];





void setup() {

  Serial.begin(9600);
  HC12.begin(9600); // Serial port to HC12
  xmotor.attach(9);
  ymotor.attach(10);
  pinMode(finish, INPUT);
  pinMode(lose, INPUT);


}

String statement = "0,";

void loop() {

  while (Serial.available()) { // If Serial monitor has data
    HC12.write(Serial.read()); // Send that data to HC-12
  }

  String rxString = "";

  if (HC12.available()) {

    xvalString = "";
    while (HC12.available()) {
      delay(2);
      char ch = HC12.read();
      rxString += ch;
    }

    int stringStart = 0;
    int arrayIndex = 0;

    for (int i = 0; i < rxString.length(); i++) {
      if (rxString.charAt(i) == ',') {
        strArr[arrayIndex] = "";
        strArr[arrayIndex] = rxString.substring(stringStart, i);
        stringStart = (i + 1);
        arrayIndex++;
      }
    }
    xvalString = strArr[0];
    yvalString = strArr[1];


    x = xvalString.toInt();
    y = yvalString.toInt();
  }

  xmotor.write(x);
  ymotor.write(y);



//
  if (digitalRead(finish) == HIGH) {
    HC12.println("win,");
    delay(15);

  }

  else if (digitalRead(lose) == HIGH) {
    HC12.println("boo,");
    delay(15);

  }
//  HC12.println(statement);
  delay(15);




}
