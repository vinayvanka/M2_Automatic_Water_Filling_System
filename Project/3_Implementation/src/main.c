/**
 * @file main.c
 * @author vanka vinaya kumar
 * @brief This is Automatic water level control system
 * @version 0.1
 * @date 2022-03-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */



/**
 * @brief 16 X 2 LCD display header file included.
 */
#include <LiquidCrystal.h>

/**
 * @brief INITIALISED ALL USER FUNCTIONS USED IN THIS PROGRAM
 * 
 */
void mode(void);
void manual(void);
void waterpump(byte waterpump_state);
void automatic(void);
void sensor_data(void);

/**
 * @brief DEFINING ATMEGA 328 PINS WITH VARIABLE NAMES
 * 
 */

#define MODE_SELECT      0 
#define MANUAL_SWITCH    1
#define MOTOR_STATE      8
#define SENSOR_1         9
#define SENSOR_2         10
#define SENSOR_3         11
#define SENSOR_4         12
#define SENSOR_5         13

/**
 * @brief DEFINING USER VARIABLES USED IN THIS PROGRAM.
 * 
 */

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

/**
 * @brief DEFINING THE ATMEGA 328 PINS TO 16 X 2 LCD PINS VARIABLES.
 * 
 */

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/**
 * @brief SETTING PIN MODES FOR ONE TIME INITIALISATION, THIS WILL RUN ONLY ONCE.
 * 
 */

void setup() {

/**
 * @brief LCD WILL START AT 16 X 2 SETTING ALL TO BLANK INITIALLY
 * 
 */

  lcd.begin(16,2);

/**
 * @brief Construct a new pin Mode object, DECLARING THE PINS AS INPUT OR OUTPUT
 * 
 */

 pinMode (MODE_SELECT,INPUT);
 pinMode (MANUAL_SWITCH,INPUT);
 pinMode (SENSOR_1,INPUT);
 pinMode (SENSOR_2,INPUT);
 pinMode (SENSOR_3,INPUT);
 pinMode (SENSOR_4,INPUT);
 pinMode (SENSOR_5,INPUT);
 pinMode (MOTOR_STATE,OUTPUT);


}
/**
 * @brief LOOP WILL RUN THE PROGRAM CONTINOUSLY
 * 
 */


void loop() {
  
  /**
   * @brief CALLING THE USER DEFINED FUNCTIONS 
   * @brief sensor_data will tell the present water level in the tank by setting the waterlevel variable
   * @brief mode function will select the mode as automatic or manual.
   * 
   */
  sensor_data();
  mode();

}

/**
 * @brief this will seletc the mode as automatic or manual by taking input from the user.
 * @brief manual and automatic functions were called by mode according to the user input.
 */

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
 /**
  * @brief manual function takes user inputto turn pump on and off by telling the waterpump function.
  * @brief water pump functioon were called according to the user
  */

void manual(void){

    Manula_ButtonState = digitalRead(MANUAL_SWITCH);
    
    if (Manula_ButtonState == HIGH) {

       waterpump(HIGH);
    }
    else{

       waterpump(LOW);
       
  }
}

/**
 * @brief this function will set water pump state and displays the water level
 * 
 * @param waterpump_state 
 */

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
/**
 * @brief automatic function will check the sensor value and according to the value analysis it will tell the water function to turn on and off the water pump.
 * 
 */

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

/**
 * @brief sensor function will sense the water level  
 * 
 */

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
