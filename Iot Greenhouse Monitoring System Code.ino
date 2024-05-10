#include <LiquidCrystal.h>
#include <SimpleDHT.h>
#include <stdio.h>




const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int pinDHT11 = 2;
SimpleDHT11 dht11;


const int light=4;
const int pump=3;
const int ldr=6;
const int soil=5;


void ldr_check(void);
void read_temperature(void);
void soil_check(void);


void setup() {
  // put your setup code here, to run once:
  pinMode(light,OUTPUT);
  pinMode(pump,OUTPUT);
    pinMode(soil,INPUT);
  pinMode(ldr,INPUT);
  
 digitalWrite(light,LOW);
  digitalWrite(pump,LOW);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GREEN HOUSE       ");
  lcd.setCursor(0,1);
  lcd.print("USING IOT");
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
read_temperature();
      ldr_check();
      soil_check();
}
void read_temperature()
{
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
    {
//      Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);   
      return;
    }
    //It will give temperature value
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMP    ");
    lcd.print((int)temperature); 
    Serial.println("TEMPERATURE:");
    Serial.println((int)temperature);
     //It will give Humidity value
    lcd.setCursor(0,1);
    lcd.print("HUMY    ");
    lcd.print((int)humidity); 
    Serial.println("HUMIDITY:");
    Serial.println((int)humidity);
    delay(2000);

    if((int)temperature>42)
    {
      lcd.clear();
        lcd.setCursor(0,0);
  lcd.print("MORE         ");
  lcd.setCursor(0,1);
  lcd.print("TEMPERATUE");
  Serial.println("MORE TEMPERATURE  ");delay(2000);
      
      
    }
  else
    {
     lcd.clear();
     lcd.setCursor(0,0);
  lcd.print("NORMAL TEMPERATURE         ");
  lcd.setCursor(0,1);
  lcd.print("NORMAL HUMIDITY");
  Serial.println("NORMAL TEMPERATURE AND NORMAL HUMIDITY");
  delay(1500);
      
      }
 delay(1500);
        
}


void ldr_check()
{
      
    if(digitalRead(ldr) == 1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      digitalWrite(light,HIGH);
      lcd.print("NIGHT VISION");
      lcd.setCursor(0,1);
      lcd.print("LIGHT ON");
      Serial.println("NIGHT VISION LIGHTS ON");
     }
       else if(digitalRead(ldr) == 0)
    {
       lcd.clear();
      lcd.setCursor(0,0);
      digitalWrite(light,LOW);
      lcd.print("DAY VISION");
      lcd.setCursor(0,1);
      lcd.print("LIGHT OFF");
      Serial.println("DAY VISION LIGHTS OFF");
     }
    delay(3000);
}
void soil_check()
{
      
    if(digitalRead(soil) == 1)
    { digitalWrite(pump,HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LAND IS DRY");
      lcd.setCursor(0,1);
      lcd.print("PUMP ON");
      Serial.println("LAND IS DRY PUMP ON");delay(2000);
      
     }
       else if(digitalRead(soil) == 0)
    {
        digitalWrite(pump,LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LAND IS WET");
      lcd.setCursor(0,1);
      lcd.print("PUMP OFF");
      Serial.println("LAND IS WET PUMP OFF");delay(2000);
     }
}

