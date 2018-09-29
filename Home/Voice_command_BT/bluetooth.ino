String voice;

void setup() {
 
  Serial.begin(9600);
  pinMode(11, OUTPUT);//fan
  pinMode(13, OUTPUT);//light
  pinMode(9,OUTPUT);//pump
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

    if (voice == "*light on")
    {
      digitalWrite(13, HIGH);
      Serial.println("LIGHT IS ON");
    }

    else if (voice == "*light off")
    {
      digitalWrite(13, LOW);
      Serial.println("LIGHT IS OFF");
    }
    else if (voice == "*fan on")
    {
      analogWrite(11, 200);
      Serial.println("FAN LEVEL 1");
    }
    
    
    else if (voice == "*level 2")
    {
      analogWrite(11, 255);
      Serial.println("FAN LEVEL 2");
    }
    
    else if (voice == "*fan off")
    {
      analogWrite(11, 0);
      Serial.println("FAN IS OFF");
    }
    else if (voice == "*pump on")
    {
      analogWrite(9, 255);
      Serial.println("Pump ON");
    }

    else if (voice == "*pump off")
    {
      analogWrite(9, 0);
      Serial.println("Pump OFF");
    }
   
    
    else
    {
    }

    voice = "";
  }
} //Reset the variable after initiating
