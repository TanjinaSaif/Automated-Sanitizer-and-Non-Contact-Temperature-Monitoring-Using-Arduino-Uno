#include<LiquidCrystal.h>
#include <Servo.h>
LiquidCrystal lcd(7,6,5,4,3,2);

//Infrared Sensor
const int IRSensor = 8;
const int led = 9;

//Temperature Sensor
const int tempSensor = A0; 
byte degree_symbol[8] = 
              {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };
              
const int trigPin = 13; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 12; // Echo Pin of Ultrasonic Sensor
Servo Myservo; //create servo object to control a servo

void setup() {
  // put your setup code here, to run once:
  {
  //IR Sensor
  pinMode(IRSensor,INPUT);
  pinMode(led,OUTPUT);

  //Temperature LCD Display
  pinMode(tempSensor, INPUT);
  lcd.begin(16,2);
  lcd.createChar(1, degree_symbol);
  lcd.setCursor(0,0);
  lcd.print("Temperature");
  lcd.setCursor(0,1);
  lcd.print("  Sensor  ");
  delay(500);
  lcd.clear();
  }
  
  Serial.begin(9600); // Starting Serial Terminal

  Myservo.attach(11);  // Signal Pin of Servo      
                                       
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.print(" Touchless ");
  Serial.print(" IR Thermometer & Sanitizer ");
  delay(10);
  Serial.print("Made By :");

  Serial.print("Adiba, Tanjina & Laka");
  delay(20);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorState = digitalRead(IRSensor);
  //Temperature calculation
  float temp_reading=analogRead(tempSensor); // reads the value of the potentiometer (value between 0 and 1023)
  float temp_celcius=temp_reading*(5.0/1023.0)*100; //Potentiometer Vout Calculation
  float temp_farenheit = (temp_celcius*1.8)+32;    //C to F convertion
  delay(10); 

  //Object detected,Will display temperature on LCD
  if(sensorState == HIGH) //If IR Sensor detects an Obstacle/Object,then sensorState is HIGH
  {
    digitalWrite(led,LOW); //IR Sensor led Off

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperature is");
    lcd.setCursor(4,1);
    lcd.print(temp_farenheit);
    lcd.write(1);
    lcd.print("F");
    delay(500);
    lcd.clear();
    //Checking Fever
    if(temp_celcius>=37.5)
    {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("High Temperature");
    lcd.setCursor(0,1);
    lcd.print("Access Denied");
    delay(500);
    }
    else
    {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Access Granted!");
    delay(500);
    }
  }
  //No object detected,Will not display temperature on LCD
  else       //If IR Sensor doesn't detects an Obstacle/Object,then sensorState is LOW
  {
    digitalWrite(led,HIGH);
    lcd.clear(); 
    lcd.setCursor(0,0);
    lcd.print("No Object");
    lcd.setCursor(0,1);
    lcd.print("Detected");
    delay(500);
    lcd.clear();
  }
  long duration, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  

  Serial.print("Distance:");
  Serial.print(cm);
  Serial.print("cm");
  delay(100);
  
  if(cm <= 20){
  Myservo.write(0);
  }
  else {
  Myservo.write(90);
  }
  
  Serial.println();
  delay(100);
}

long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;  
}
