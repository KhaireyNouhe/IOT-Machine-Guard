//IOT Machine-Guard
//Coded by Khairey Nouhe (khaireynouhe@gmail.com) 

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.

/************************** Installing Libraries ***********************************/

#include "config.h"                // Include file for boker connection data
#include "max6675.h"              // Include Library for Temperature Sensor
#include "EmonLib.h"             // Include Library for Current Sensor


#define CURRENT_CAL 62.6       // Calibration for Current Sensor
EnergyMonitor emon1;          // Create an instance for Current Sensor

#define sound_PIN 34        // don't change it
#define vib_PIN 35         // don't change it
#define smoke_PIN 33      // don't change it
#define current_PIN 39   // don't change it
#define alarm_PIN 25   // don't change it

// Temperature Sensor Setup >>> Use 3 Digital Pins

int thermoDO = 19; // SO
int thermoCS = 23;
int thermoCLK = 5; // SCK
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

/************************** Installing Libraries ***********************************/

float Normal_Sound_Level= 250;     
float Normal_Vib_Level = 5000;    
int Normal_Smoke_Level= 20;  
int Normal_Temp_Level = 50;    
float Normal_Current_Level= 20.00;   // 20Amp 
float First_Current_Reading=70.00;   // 70 Amp

    
boolean is_Relay_on=true;
boolean is_Machine_on=true;
String Machine_Power;
String Machine_Power_Status; 
String Alarm_State;
boolean AlarmState=false;
String reason;
int relay_PIN=32;    // don't change it


// set up the 'Analog Sensor' feeds

//AdafruitIO_Feed *Sound = io.feed("sound-intensity");
AdafruitIO_Feed *temperature = io.feed("temperature");
AdafruitIO_Feed *Vibration = io.feed("vibration-intensity");
AdafruitIO_Feed *Smoke = io.feed("smoke-intensity");
AdafruitIO_Feed *Current = io.feed("current");

// set up the 'Digital Power' feed
AdafruitIO_Feed *power = io.feed("power");

void setup() {
pinMode(sound_PIN, INPUT);
pinMode(vib_PIN, INPUT);
pinMode(smoke_PIN, INPUT);
pinMode(current_PIN, INPUT);
pinMode(relay_PIN, OUTPUT);
pinMode(alarm_PIN, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

      
  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

power->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.println("Connecting.......");
    Serial.println("If it Takes a Long Time, Check WIFI Username/Password!");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  
  if (is_Relay_on==true){
  power->save(HIGH);
}
  // initialize Current Sensor
 emon1.current(current_PIN, CURRENT_CAL);       // Current: input pin, calibration.
}


void loop() {

   io.run();  // connect to Adafruit.io broker
  
  /*===============================Machine Power Setup============================================================*/

switch (is_Relay_on) {
    case true:
      digitalWrite(relay_PIN,HIGH);
      Machine_Power="ON"; 
      AlarmState=false;
      Alarm_State="OFF";
      
      break;
      
    case false:
      digitalWrite(relay_PIN,LOW); 
      is_Machine_on=false;
      Machine_Power="OFF";
      AlarmState=true;
      Alarm_State="Triggered";
           
       break;
       
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }

while (( is_Machine_on)==true) {

  /*===============================Sound Setup============================================================*/

  float sound_intense = analogRead(sound_PIN);
 if (sound_intense>Normal_Sound_Level){
  is_Relay_on= false;
  reason="((((((Abnormal Sound Values))))))";
}
   
/*===============================Vibration Setup============================================================*/

float Vib_intense = analogRead(vib_PIN);

  if (Vib_intense>Normal_Vib_Level){
  is_Relay_on= false;
  reason="((((((Abnormal Vibration Values))))))";
}
 
 /*===============================Smoke Setup============================================================*/

int smoke_intense = analogRead(smoke_PIN);

if (smoke_intense>Normal_Smoke_Level){
 is_Relay_on= false;
 reason="((((((Abnormal Smoke Values))))))";
}

/*===============================Temperature Setup============================================================*/

if (thermocouple.readCelsius()>Normal_Temp_Level){
 is_Relay_on= false;
 reason="((((((Abnormal Temperature Values))))))";
}
 
/*===============================Current Setup============================================================*/

  emon1.calcVI(20,100);         // Calculate all. No.of half wavelengths (crossings), time-out
  
  float currentDraw   = emon1.Irms-2;            //extract Irms into Variable
  int supplyVoltage   = 220;                    //extract Vrms into Variable

  if (currentDraw<0){
    currentDraw=-currentDraw*0;
  }
else{
  currentDraw=currentDraw;
}

if (currentDraw>=First_Current_Reading){
  currentDraw=0;
} 

  if (currentDraw>Normal_Current_Level){
  is_Relay_on= false;
  reason="((((((Abnormal Current Withdrawal Values))))))";
}



/*===============================Broker Data Outputs============================================================*/
Current->save(currentDraw);
temperature->save(thermocouple.readCelsius());
Vibration->save(Vib_intense);
Smoke->save(smoke_intense); 
         
//Sound->save(sound_intense);
 /*===============================Serial Data Outputs============================================================*/

  Serial.println(" ");
  Serial.println("..................................................");
  Serial.println(" ");
  Serial.print("Recieved Machine Power: ");
  Serial.println("ON");
  Serial.println(" ");
  Serial.println("----->Sending----->-----> (((WIFI)))");
  Serial.println(" ");
  Serial.print("Machine Power: "); // Print the voltage.
  Serial.println(Machine_Power); // Print the voltage.
  Serial.print("Alarm State: "); // Print the voltage.
  Serial.println(Alarm_State); // Print the voltage.
  Serial.print("Sound Intensity: "); // Print the voltage.
  Serial.println(sound_intense);
  Serial.print("Vibration Intensity: "); // Print the voltage.
  Serial.println(Vib_intense); // Print the voltage.
  Serial.print("Smoke Density: "); // Print the voltage.
  Serial.println(smoke_intense); // Print the voltage.
  Serial.print("Temperature: "); 
  Serial.println(thermocouple.readCelsius());
  Serial.print("Current: ");
  Serial.println(currentDraw);
  Serial.print("Voltage: ");
  Serial.println(supplyVoltage);
  Serial.print("Watts: ");
  Serial.println(currentDraw * supplyVoltage);
  //power->save(HIGH); 
 // wait one second (1000 milliseconds == 1 second)

 delay(5000);
 break;
}


if (AlarmState==true) {
 dacWrite(alarm_PIN, 255); // buzzer ON
  delay(600);
  dacWrite(alarm_PIN, 0);
}
else{
  dacWrite(alarm_PIN, 0);
}


while (( is_Machine_on)==false) {

 /*===============================Serial Data Outputs============================================================*/

  Serial.println(" ");
  Serial.println("..................................................");
  Serial.println(" ");
  Serial.println(">>>>>>>>>>Stopped Sending<<<<<<<<<<");
  Serial.println(" ");
  Serial.print("Recieved Machine Power: ");
  Serial.println("OFF");
  Serial.print("Machine Power: "); // Print the voltage.
  Serial.println(Machine_Power); // Print the voltage.
  Serial.print("Alarm State: "); // Print the voltage.
  Serial.println(Alarm_State); // Print the voltage.
  Serial.print("Reason: ");
  Serial.print(reason);
  Serial.println(" ");
 // wait one second (1000 milliseconds == 1 second)
power->save(LOW);
 delay(1000);
 break;
}

}


//=========================Adafruit.io Power Toggle Switch Setup=======================================

void handleMessage(AdafruitIO_Data *data) {
  if(data->toPinLevel() == HIGH){
    
    Serial.print("Recieved Machine Power: ");
    Serial.println("ON");
       is_Relay_on=true;
         is_Machine_on=true; 
       
  }else{
    Serial.print("Recieved Machine Power: ");
    Serial.println("OFF");
       is_Relay_on=false;
       reason="(((((( Manual Online Shut Down ))))))";
      
  }   
}

