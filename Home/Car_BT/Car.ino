String voice;

void setup() {
 
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  
}
/*-----------------------------------------------------------------------*/
void loop() {

  while (Serial.available()) { //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {
      break; //Exit the loop when the # is detected after the word
    }
    voice += c; //Shorthand for voice = voice + c
  }
  if (voice.length() > 0) {
    Serial.println(voice);

    if (voice == "*go")
    {
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      Serial.println("I'm moving front");
    }

    else if (voice == "*back")
    {
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      Serial.println("I'm moving back");
    }
   else if (voice == "*right")
    {
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      delay(5000);
      Serial.println("I'm moving right");
    }
    else if (voice == "*left")
    {
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      delay(5000);
      Serial.println("I'm moving LEFT");
    }
   
     else if (voice == "*stop")
    {
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      Serial.println("Uff!!");
    }
    else
    {
    }

    voice = "";
  }
} //Reset the variable after initiating
