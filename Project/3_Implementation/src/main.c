
#include <LiquidCrystal.h>


void mode(void);
void manual(void);
void waterpump(byte waterpump_state);
void automatic(void);
void sensor_data(void);



#define MODE_SELECT      0 
#define MANUAL_SWITCH    1
#define MOTOR_STATE      8
#define SENSOR_1         9
#define SENSOR_2         10
#define SENSOR_3         11
#define SENSOR_4         12
#define SENSOR_5         13


byte Mode_ButtonState = LOW;
byte Manula_ButtonState = LOW;
byte Sensor1State = LOW;
byte Sensor2State = LOW;
byte Sensor3State = LOW;
byte Sensor4State = LOW;
byte Sensor5State = LOW;
byte LastPumpState;
byte water_pump_state;

int waterlevel = 0;


const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  lcd.begin(16,2);

 pinMode (MODE_SELECT,INPUT);
 pinMode (MANUAL_SWITCH,INPUT);
 pinMode (SENSOR_1,INPUT);
 pinMode (SENSOR_2,INPUT);
 pinMode (SENSOR_3,INPUT);
 pinMode (SENSOR_4,INPUT);
 pinMode (SENSOR_5,INPUT);
 pinMode (MOTOR_STATE,OUTPUT);


}

void loop() {
  
  sensor_data();
  mode();

}

void mode(void){

  Mode_ButtonState = digitalRead(MODE_SELECT);

  if(Mode_ButtonState==HIGH)
  {
    manual();
  }
  else 
  {
    automatic();
  }
}

void manual(void){

    Manula_ButtonState = digitalRead(MANUAL_SWITCH);
    
    if (Manula_ButtonState == HIGH) {

       waterpump(HIGH);
    }
    else{

       waterpump(LOW);
       
  }
}

void waterpump(byte waterpump_state){

  if(waterpump_state == HIGH){
    
    digitalWrite( MOTOR_STATE , HIGH );
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(String("WATER LEVEL: ") + String(waterlevel)+ String("%"));
    lcd.setCursor(0,1);
    lcd.print("PUMP : ON!");
    water_pump_state = HIGH;
    
  }
  
  else {
    digitalWrite( MOTOR_STATE , LOW);
    
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print(String("WATER LEVEL: ") + String(waterlevel)+ String("%"));
    lcd.setCursor(0,1);
    lcd.print("PUMP : OFF!");
    water_pump_state = LOW;
    
  }

  delay(300);
  
}


void automatic(void){

  if(waterlevel<20){
    waterpump(HIGH);
    LastPumpState = HIGH;
  }
  
  else if (waterlevel==100){
    waterpump(LOW);
    LastPumpState = LOW;
  }
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(String("WATER LEVEL: ") + String(waterlevel)+ String("%"));
    lcd.setCursor(0,1);
    
    if(water_pump_state == HIGH){
      lcd.print("PUMP : ON!");
    }
    else if(water_pump_state == LOW){
        lcd.print("PUMP : OFF!");
      }
      delay(300);
  

}

void sensor_data(void){

Sensor1State = digitalRead(SENSOR_1);
Sensor2State = digitalRead(SENSOR_2);
Sensor3State = digitalRead(SENSOR_3);
Sensor4State = digitalRead(SENSOR_4);
Sensor5State = digitalRead(SENSOR_5);



  if(Sensor1State==0 && Sensor2State==0 && Sensor3State==0 && Sensor4State==0 && Sensor5State==0){

waterlevel=0;
  }
  if(Sensor1State==1 && Sensor2State==0 && Sensor3State==0 && Sensor4State==0 && Sensor5State==0){

waterlevel=20;
  }
  if(Sensor1State==1 && Sensor2State==1 && Sensor3State==0 && Sensor4State==0 && Sensor5State==0){

waterlevel=40;
  }
  if(Sensor1State==1 && Sensor2State==1 && Sensor3State==1 && Sensor4State==0 && Sensor5State==0){

waterlevel=60;
  }if(Sensor1State==1 && Sensor2State==1 && Sensor3State==1 && Sensor4State==1 && Sensor5State==0){

waterlevel=80;
  }
  if(Sensor1State==1 && Sensor2State==1 && Sensor3State==1 && Sensor4State==1 && Sensor5State==1){

waterlevel=100;
  }

}
