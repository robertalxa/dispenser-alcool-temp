#include <Ultrasonic.h>
#include <Servo.h>
#include <Wire.h> // I2C library, required for MLX90614
#include <SparkFunMLX90614.h> //Click here to get the library: http://librarymanager/All#Qwiic_IR_Thermometer by SparkFun


IRTherm therm; // Create an IRTherm object to interact with throughout
//Definições Distancia
#define pino_trigger 6
#define pino_echo 7
#define pino_servo 3
#define pino_led_verde 12
#define pino_led_vermelho 13

//Definições Servo
Servo servo;
int pos = 0;

Ultrasonic ultrasonic(pino_trigger, pino_echo);
int distance;

void setup() {

  //----LEDs----
  pinMode(pino_led_vermelho, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);
  //------------
  
  //----Servo------
  Serial.begin(9600);
  servo.attach(pino_servo);
  servo.write(90);
  //---------------

  //----Sensor de temperatura----
  Serial.begin(115200); // Initialize Serial to log output
  Wire.begin(); //Joing I2C bus
  
  if (therm.begin() == false){ // Initialize thermal IR sensor
    Serial.println("Módulo de temperatura inativo");
    while(1);
  }
  
  Serial.println("Sensor de temperatura ativo");
  therm.setUnit(TEMP_C);  
  pinMode(LED_BUILTIN, OUTPUT); // LED pin as output
  //------------------------------


  //Sensor de Distância
  
  //------------------

  
}

void loop() {
  distance = ultrasonic.read();
  
  Serial.print("Distância em CM: ");
  Serial.println(distance);
  
  if(distance < 16){

    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    
    if (therm.read())
    {
      float temp = therm.object() + 2.3;
      Serial.print("Temperatura corporal: " + String(temp, 2));

      if(temp >= 33 && temp < 38){
          digitalWrite(pino_led_verde, HIGH);
          digitalWrite(pino_led_vermelho, LOW);
          servo.write(0);
      }else{
          digitalWrite(pino_led_verde, LOW);
          digitalWrite(pino_led_vermelho, HIGH);
          servo.write(90);
      }
      
      delay(2000);
      digitalWrite(pino_led_vermelho, LOW);
      digitalWrite(pino_led_verde, LOW);
      Serial.println();
    }
    digitalWrite(LED_BUILTIN, LOW);
    
  }else{
    servo.write(90);
  }

  digitalWrite(pino_led_verde, LOW);
  

  delay(500);
}
