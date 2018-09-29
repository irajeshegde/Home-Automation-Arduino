#include <SoftwareSerial.h>
int a = 0, b, g = 0, l, y, n, time;
unsigned long run_time;
char c;
unsigned int digi[6], digit[6];
String number, content, reference1, reference2, time1;
SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{

  Serial.begin(9600);
  pinMode(9, OUTPUT);//pump
  pinMode(12, OUTPUT);//fan
  pinMode(13, OUTPUT);//light

  Serial.println("PROJECT STARTED!");


  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() // run over and over
{
  run_time = millis();

  if (mySerial.available())
  {
    c = mySerial.read();
    Serial.write(c);
    delay(100);

    while (c == '"')
    {

      c = mySerial.read();
      delay(100);

      if (c == '+')
      {
        number = "";


        for (b = 0; b < 13; b++)
        {

          number += c;
          c = mySerial.read();
          delay(100);
        }

        Serial.println("number :");
        Serial.println(number);

      }

    }
    if (c == '#')
    {
      content = "";
      for (y = 0; y < 10; y++)
      {
        c = mySerial.read();
        if (c == '*')
        {
          y = 11;
        }
        else
        {
          content += c;
        }
      }
      Serial.println("content :");
      Serial.println(content);
      g = 1;
    }



  }

  if (g == 1)
  {
    if (number == "+910123456789" && content == "light on")
    {
      digitalWrite(13, HIGH);
      reference1 = "light is on sir";
      digi[0] = millis() / 1000;
      digit[0] = 1;
      l = 1;
    }
    if (number == "+910123456789" && content == "light off")
    {
      digitalWrite(13, LOW);
      reference1 = "light is off sir";
      reference2 = "light was on for ";
      digi[1] = millis() / 1000;
      digit[1] = 1;
      l = 1;
    }
    if (number == "+910123456789" && content == "pump on")
    {
      //Serial.println("pump is on");
      digitalWrite(9, HIGH);
      reference1 = "pump is on sir";
      digi[2] = millis() / 1000;
      digit[2] = 1;
      l = 1;
    }
    if (number == "+910123456789" && content == "pump off")
    {
      //Serial.println("pump is off");
      digitalWrite(9, LOW);
      reference1 = "pump is off sir";
      reference2 = "pump was on for ";
      digi[3] = millis() / 1000;
      digit[3] = 1;
      l = 1;
    }
    if (number == "+910123456789" && content == "fan on")
    {
      //Serial.println("fan is on");
      digitalWrite(12, HIGH);
      reference1 = "fan is on sir";
      digi[4] = millis() / 1000;
      digit[4] = 1;
      l = 1;
    }
    if (number == "+910123456789" && content == "fan off")
    {
      //Serial.println("fan is off");
      digitalWrite(12, LOW);
      reference1 = "fan is off sir";
      reference2 = "fan was on for ";
      digi[5] = millis() / 1000;
      digit[5] = 1;
      l = 1;
    }
    if (number != "+910123456789" && (content == "fan off" || content == "fan on" || content == "pump off" || content == "pump on" || content == "light off" || content == "light on"))
    {
      mySerial.print("AT+CMGF=1");
      delay(100);
      mySerial.write(0x0d);
      delay(100);
      mySerial.println("AT+CMGS=\"+910123456789\"\r");
      delay(1000);
      mySerial.print(number);
      delay(1000);
      mySerial.print(" had tried to execute ");
      delay(1000);
      mySerial.print(content);
      delay(1000);
      mySerial.write(0x0d);
      delay(100);
      mySerial.write(0x1a);
      delay(200);
    }
    g = 0;
  }

  if (l == 1)
  {
    l = 0;
    mySerial.print("AT+CMGF=1");
    delay(100);
    mySerial.write(0x0d);
    delay(100);
    mySerial.println("AT+CMGS=\"+910123456789\"\r");
    delay(1000);
    mySerial.println(reference1);
    delay(1000);
    mySerial.write(0x0d);
    delay(100);
    mySerial.write(0x1a);
    delay(200);

    for (a = 0; a < 5; a = a + 2)
    {
      if (digit[a] == 1)
      {
        n = a;
        delay(100);
        n = n + 1;
        delay(100);

        if (digit[n] == 1)
        {

          digit[a] = 0;
          delay(150);
          digit[n] = 0;
          delay(150);
          time = digi[n] - digi[a];
          Serial.print(reference2);
          Serial.print(time);
          Serial.println(" seconds.");
          time1 += time;

          mySerial.print("AT+CMGF=1");
          delay(100);
          mySerial.write(0x0d);
          delay(100);
          mySerial.println("AT+CMGS=\"+910123456789\"\r");
          delay(1000);
          mySerial.println(reference2);
          delay(1000);
          mySerial.print(time1);
          delay(1000);
          mySerial.print(" seconds.");
          delay(1000);
          mySerial.write(0x0d);
          delay(100);
          mySerial.write(0x1a);
          delay(200);
          time1 = "";
        }
      }

    }

  }
}
// +CMT: "+910123456789",,"16/10/29,18:28:49+22"
//  Fds



