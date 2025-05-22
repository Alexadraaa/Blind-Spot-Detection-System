//Pins used def
const int trigPin = 7; //trigger pin for sensor
const int echoPin = 8; //echo pin for sensor
const int motorPin = 4; //pin for vibration motor
const int switchPin = 2; //pin to control switch ON/OFF
const int redPin = 11;    // red pin RGB LED
const int greenPin = 10;  // green pin RGB LED
const int bluePin = 9; 	// blue pin RGB LED

//constants for distance def
const int c1 = 200;
const int c2 = 300;

//variable def
int dist;
int switchState;


void setup()
{
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  
  Serial.begin(9600);
}
void loop(){
  
    switchState = digitalRead(switchPin);
  
  if(switchState==HIGH) {
    
    dist = getDistance();
    Serial.print("Distance: ");
    Serial.print(dist); // Print the output in serial monitor
    Serial.println(" cm");
  
  if(dist > c2)//safe distance
  {
    setColor(0, 0, 0); //led off
    digitalWrite(motorPin, LOW); //vibration motor off
  }	
  else if(dist < c1) //critical warning
  {
    setColor(255, 0, 0); //rgb led red
    digitalWrite(motorPin, HIGH); //no vibration motor
  }
  else if(c1< dist <=c2) //first warning
  {
    setColor(255, 165, 0); //  rgb led orange
    digitalWrite(motorPin, LOW); //no vibration motor
  }
    
  }
    else if(switchState == LOW)
  {
    setColor(0, 0, 0); //led off
  }

  delay(200);
}

  
  //func to calculate distance
  int getDistance()
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10); 

    digitalWrite(trigPin,LOW);

    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.0344 / 2;

    return distance;
  }

    //func for RGB Led color
  void setColor(int red, int green, int blue)
  {
    analogWrite(redPin,red);
    analogWrite(greenPin,green);
    analogWrite(bluePin,blue);
  }

