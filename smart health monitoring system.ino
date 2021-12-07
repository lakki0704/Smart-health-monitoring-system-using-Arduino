// only on pressing the buttons you can start measurement.
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#define DHTPIN A0
#define DHTTYPE DHT22
DHT dht(DHTPIN,DHTTYPE);
float voltage;
float celsius;
int valPulse;
int pulsePin = A2;
//const int temperaturePin = A0;
String seconds;
long duration;
float BMI2;
int buzzerpin = 2,button_1=A3,button_2=A4,button_3=A5,button_4 = 4;

int pir_sensor = 7, triggerPin = 5, echoPin = 6, triggerpin_2 = 4, echopin_2 = 3;
int pir_reader, time, distance;
int minDistance = 100;
int maxDistance = 400;
float height2 ;
float weightKG ;

void setup()
{
  //pinMode(temperaturePin, INPUT);
  pinMode(button_1,INPUT);
  pinMode(button_2,INPUT);
  pinMode(button_3,INPUT);
  pinMode(button_4,INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("M&I PROJECT");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("HEALTH MONITORING");
  lcd.setCursor(5, 2);
  lcd.print("SYSTEM");
  delay(3000);
  lcd.clear();
  lcd.println("Press the Buttons");
  lcd.setCursor(0,2);
  lcd.print("  1   2   3   4 ");
  pinMode(7, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerpin,OUTPUT);
  pinMode(triggerpin_2, OUTPUT);
  pinMode(echopin_2, INPUT);
}
void loop()
{ 
  lcd.println("Press the Buttons");
  lcd.setCursor(0,2);
  lcd.print("  1   2   3   4 ");
if(digitalRead(button_1)== HIGH)
{ 
  dht.begin(); 
  here:
  delay(500);
  lcd.clear();
  lcd.print("Calculating....");delay(7000);
  celsius=dht.readTemperature();
  if(isnan(celsius))
  {
    Serial.println("Failed to read from dht");
    goto here;
  }
  lcd.clear();
  lcd.print("Body Temp. : ");
  celsius=celsius+6;
  lcd.print(celsius);
  lcd.print("C");delay(3000);
  if(celsius>38)
  {   lcd.clear();
      digitalWrite(buzzerpin, HIGH);
      lcd.print("High temp");
      delay(4000);
      digitalWrite(buzzerpin, LOW);
  }
  else
  {
    lcd.clear();
    lcd.print("Normal Temp");
    delay(4000);
  }
  lcd.clear();
  
  for (int i=10; i >= 0; i--){
    seconds = String(i);
    lcd.print("PLEASE HOLD.." + seconds);
    lcd.setCursor(0, 1);
    lcd.print("BPM: ");
    valPulse = analogRead(pulsePin);
    valPulse = valPulse/6;
    lcd.print(valPulse);
    lcd.print(" Pulse");
    lcd.print("          ");
    delay(1000);
    lcd.clear();
  } 
  lcd.print("Temperature:");lcd.print(celsius);lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Pulse : ");lcd.print(valPulse);
  while(digitalRead(button_1)== 0);
  delay(250); 
  lcd.clear();
}
if(digitalRead(button_2)== HIGH)
{    
 lcd.clear();
 Serial.begin(9600);
 //Print the Values on LCD

 Serial.println("Enter your Weight in KGs");
 lcd.print("Enter your");lcd.setCursor(0, 1);
 lcd.print("Weight in Kg");
 while(Serial.available()==0);           //Wait for user input
 lcd.clear();
 weightKG = Serial.parseFloat(); 
 lcd.print("Weight: ");
 lcd.print(weightKG);
 lcd.print ("kg");
 delay(4000);
 lcd.clear();

 Serial.println("Enter your height in cm");
 lcd.print("Enter your");lcd.setCursor(0, 1);
 lcd.print("Height in cm");
 delay(100);
 while(Serial.available()==0);            //Wait for user input
 lcd.clear();
 height2 = Serial.parseFloat();   
 lcd.print("Height: ");
 lcd.print(height2);
 lcd.print ("cm");
 delay(4000);
 lcd.clear();
  
 BMI2= weightKG/(height2*height2);
 BMI2= BMI2*10000;
 lcd.clear();

 lcd.print("BMI: ");
 lcd.print(BMI2,4);
 
//Categorizing BMI
  if (BMI2<18.5){
  lcd.setCursor(1, 1);
  lcd.print("UNDERWEIGHT");
  delay(4000);
  }
  else if (BMI2>18.5&&BMI2<25){
  lcd.setCursor(6, 1);
  lcd.print("NORMAL");
  delay(4000);
  }
  else if (BMI2>=25&&BMI2<30){
    lcd.setCursor(2, 1);
  lcd.print("OVERWEIGHT");
  delay(4000);
  }
  else if (BMI2>=30&&BMI2<35){
    lcd.setCursor(0, 1);
  lcd.print("MODERATELY ");
  lcd.print("OVERWEIGHT");
  delay(4000);
  }
  else if (BMI2>=35){
    lcd.setCursor(0, 1);
  lcd.print("SEVERELY ");
  lcd.print("OBESE");
  delay(4000);
  } 
  while(digitalRead(button_2)==0);
  delay(550);
  lcd.clear();  
}

if(digitalRead(button_3)== HIGH)
{
  lcd.clear();
  delay(350);
  while(1)
  {
    // Duration will be the input pulse width and distance will 
    //be the distance to the obstacle in centimeters
    int duration, distance;
    // Output pulse with 1ms width on trigPin
    digitalWrite(triggerPin, HIGH); 
    delay(100);
    digitalWrite(triggerPin, LOW);
    // Measure the pulse input in echo pin
    duration = pulseIn(echoPin, HIGH);
    if(digitalRead(button_3)==HIGH){lcd.clear();digitalWrite(buzzerpin, LOW);break;}
    // Distance is half the duration devided by 29.1 (from datasheet)
    distance = (duration/2) / 29.1;
    // if distance less than 0.5 meter and more than 0 (0 or less means over range) 
    if (distance <= 100 && distance >= 0) 
    {
       // Buzz
       delay(100);
      if(digitalRead(button_3)==HIGH){lcd.clear();digitalWrite(buzzerpin, LOW);break;}
      lcd.setCursor(0,0);
      lcd.print("Human");
      lcd.setCursor(0,1);
      lcd.print("Detected      ");
      digitalWrite(buzzerpin, HIGH);
}
    else 
    {
      // Don't buzz
      delay(100);
      if(digitalRead(button_3)==HIGH){lcd.clear();digitalWrite(buzzerpin, LOW);break;}
      lcd.setCursor(0,0);
      lcd.print("Human");
      lcd.setCursor(0,1);
      lcd.print("Not Detected");
      digitalWrite(buzzerpin, LOW);
    }
    // Waiting 60 ms won't hurt any one
    if(digitalRead(button_3)==HIGH){lcd.clear();digitalWrite(buzzerpin, LOW);break;}
    delay(40);
    if(digitalRead(button_3)==HIGH){lcd.clear();digitalWrite(buzzerpin, LOW);break;}
  } 
  delay(1000);
}
  
if(digitalRead(button_4)== HIGH)
{
  lcd.clear();
  //medicine reminder
  lcd.println("Look At Serial  ");
  lcd.setCursor(0,2);
  lcd.print("    Monitor ");
  Serial.println("(hours) : ");
  while (Serial.available()==0){}            
  long int hours = Serial.parseInt();
  lcd.clear();
  lcd.print(hours);
  lcd.print(" : ");
  delay(1000);
  Serial.println("(minutes) : ");
  while (Serial.available()==0){}            
  long int mins = Serial.parseInt(); 
  lcd.print(mins);
  lcd.print(" : ");
  delay(1000);
  Serial.println("(seconds) : ");
  while (Serial.available()==0){}            
  long int seconds = Serial.parseInt(); 
  lcd.print(seconds);
  lcd.clear();
  
  long int current_time =(hours*3600)+(mins*60)+(seconds);
    lcd.print(current_time);
    delay(3000);
    lcd.clear();
  long int i;
   
 for(i= current_time ; i< (current_time+(86400)); i++)
 {
  if(i == 28800)
  {   //8 am 
    digitalWrite(buzzerpin,HIGH);
     // Send 1KHz sound signal...   
    lcd.print("Medicine time");
    while(digitalRead(button_4)==LOW);
    digitalWrite(buzzerpin,LOW);
    lcd.clear();
    break;
  }
  else if(i == 72000)
  {//8 pm 
    digitalWrite(buzzerpin,HIGH);
     // Send 1KHz sound signal...   
    lcd.print("Medicine time");
    while(digitalRead(button_4)==LOW);
    digitalWrite(buzzerpin,LOW);
    lcd.clear();
    break;
  }
  else
  {
      lcd.setCursor(0,0);
      lcd.print("Your medicine");
      lcd.setCursor(0,1);
      lcd.print("time is after :");
       delay(1000);
    
    if(i<28800 )
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(28800-i );
      lcd.setCursor(0,1);
      lcd.print("seconds");
      delay(1000);
      lcd.clear();
    }
    else if (i>28000 && i<72000)
    {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print( 72000-i);
     lcd.setCursor(0,1);
     lcd.print("seconds");
     delay(1000);
     lcd.clear();
    }
     else if (i>72000)
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print( 86400-i + 28800);
      lcd.setCursor(0,1);
      lcd.print("seconds");
      delay(2000);
      lcd.clear();
     }
  }
 }
  delay(350); 
  digitalWrite(buzzerpin,LOW); 
  }
 }
