#include <Servo.h> 

Servo myservo;

#define sensorPin A0 // Temperature sensor
#define sensorPin A1 // Humidity sensor

#define SERVO_3_ID 3 //Flap
#define SERVO_6_ID 6 //Pump

float refTemp =24.0;
float value = 0;

void setup() {

  //Define the LED
  pinMode(2,OUTPUT); // LED Bleu
  pinMode(4,OUTPUT); // LED Orange
  pinMode(8,OUTPUT); // LED Rouge
  
  //Define the; Motors
  myservo3.attach(3); // Flap
  myservo3.write(0);

  myservo6.attach(6); // Pump
  myservo6.write(6);
  
  // Initialize serial communication for the motors
  Serial.begin(9600);

}

void loop() {
  
  //TEMPERATURE CALCULUS


  int value = analogRead(0);
  Serial.print("Sensor value :");
  Serial.print(value);
  
  // Get a reading from the temperature sensor:
  int reading = analogRead(sensorPin);

  // Convert the reading into voltage:
  float voltage = reading * (5000 / 1024.0);

  // Convert the voltage into the temperature in Celsius:
  float temperature = (voltage - 500) / 10;

  // Print the temperature in the Serial Monitor:
  Serial.print(temperature);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("C");

  delay(1000); // wait a second between readings
  
    if(temperature < refTemp) {
        
    myservo3.write(180);

    digitalWrite(4, LOW);
    digitalWrite(8, LOW);
    digitalWrite(2, HIGH);

    delay(1000);
  }
    if(temperature > refTemp) {
     
    myservo3.write(0);

    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    digitalWrite(8, HIGH);

    delay(1000);
  }

    if(temperature == refTemp) {

     digitalWrite(8, LOW);
     digitalWrite(2, LOW);
     digitalWrite(4, HIGH);

  }
  delay(1000);


  //HUMIDITY CALCULUS

  value = analogRead(1);
  float tension = value*5.0/1023.0;            
  float humidity = tension*100.0/3.5;  
  Serial.print(humidity);
  Serial.println("%");

  //If the humidity is lower than 50% activate the pump on pin 6
  if (humidity < 50) {    
    digitalWrite(6, HIGH);
  }

  //If the humidity is higher than 50%, don't activate the pump on pin 6
  else {
    digitalWrite(6, LOW);
  }
  delay(1000);

}
