
#define RELAY1  7  

const int sensorPin=A1;
const int threshold= 100;

int state=HIGH;    //the current state of the OUTPUT pin
int reading;       // current reading drom the INPUT pin
int previous=LOW;  //the previous reading from the INPUT pin

long time= 0; // the last time the OUTPUT pin was toggled
long debounce= 200; // the debounce time, increase if the output flickers

String message; //string that stores the incoming message


void setup()
{    
Serial.begin(9600);
pinMode(RELAY1, OUTPUT);       
pinMode(sensorPin, INPUT);
}

  void loop()
{
  int val = analogRead(sensorPin);

if(val>sensorPin)
{
  reading=HIGH;
}
else
{
  reading=LOW;
}

if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }

  previous=reading;
  
    while(Serial.available())
  {//while there is data available on the serial monitor
    message+=char(Serial.read());//store string from serial command
  }
  if(!Serial.available())
  {
    if(message == "lights on")
    {//if data is available
      Serial.println(message); //show the data
      digitalWrite(RELAY1, HIGH);
      message=""; //clear the data
    }
    if(message == "lights off")
    {
      Serial.println(message);
      digitalWrite(RELAY1, LOW);
      message="";
    }

    
  }
  
}
