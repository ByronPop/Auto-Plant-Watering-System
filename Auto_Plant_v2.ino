// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include <SPI.h>
#include <SD.h>

RTC_DS1307 rtc;
File myFile;

// soil moisture set up

int input = 2; // Relay input for pump
int running_moisture_val_total = 0;
int average_moisture_val = 0;
int count = 0;
int soilMoistureValue = 0;

// const int superDryLevel = 540;   //dry Value
// const int midLevel = 500; // mid level
// const int wetLevel = 400;  //Submersed water value

// micro sd card set up

DateTime now;
int newHour = 0;
int oldHour = 0;

void save_moisture_level(int soil_moisture_level) {
  
    myFile = SD.open("test.txt", FILE_WRITE);
    DateTime now = rtc.now();

    myFile.print(now.year(), DEC);
    myFile.print('-');
    myFile.print(now.month(), DEC);
    myFile.print('-');
    myFile.print(now.day(), DEC);
    myFile.print(" ");
    myFile.print(now.hour());
    myFile.print(":");
    myFile.print(now.minute());
    myFile.print(":");
    myFile.print(now.second());
    myFile.print(",");
    myFile.print(soil_moisture_level);
    myFile.print(",");
    myFile.print(plant_water_time(soil_moisture_level));
    myFile.println("");
    myFile.close();    
  }

double plant_water_time (double avg_soil_moisture) {

  double watering_time;
  
  watering_time =  (avg_soil_moisture/20) - 25;
  
  return watering_time;
  
}
  
void setup() {
  
  // Setting up moisture sensor input
 Serial.begin(9600);
 pinMode(input, OUTPUT);
 digitalWrite(input, HIGH);

// setting up sd card

Serial.print("Initializing SD card...");
if (!SD.begin(10)) {
Serial.println("initialization failed!");
while (1);
}
Serial.println("initialization done.");

// RTC Logic 
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    
  }
   delay(3000);
}


void loop() {

DateTime now = rtc.now(); // Getting time readout from RTC module
soilMoistureValue = analogRead(A0);  // Read-out from Sensor insert into soil
save_moisture_level(soilMoistureValue); // saving moisture level to SD card
  
  if (now.hour() == 9) // At 9am, the system tests the soil moisture levels
  {
    for (count=0; count <=60;count++) // This section takes 60 soil moisture samples (on each minute) to calculate an average moisture level. 
                                      //  Average is used to mitigate any erroneous sensor readings.  
    {
      soilMoistureValue = analogRead(A0); 
      running_moisture_val_total = running_moisture_val_total + soilMoistureValue;
      
      Serial.print("Printing round: ");
      Serial.print(count);
      Serial.print(". Soil moisture level is: ");
      Serial.print(soilMoistureValue);
      Serial.println();
      
      save_moisture_level(soilMoistureValue); // saving moisture level to SD card
      
      Serial.println("Writing to File");
      
      delay(60000);
    } 
     average_moisture_val = running_moisture_val_total/60; // calculating average moisture level
     
     Serial.println("Average moisture level is:  ");
     Serial.print(average_moisture_val);
     Serial.println();
     
     int watering_period =  plant_water_time(average_moisture_val); // calculating watering time based on moisture level

     Serial.println("Watering period is:  ");
     Serial.print(watering_period);
     Serial.print(" Seconds.");
     Serial.println();
     
    if (watering_period > 0) // Watering plant. To avoid tiny watering amounts I set the threshold at 2 seconds. 
    { 
      Serial.println("WATERING!");
      digitalWrite(input, LOW); //turning pump on
      delay(watering_period*1000); // pumping for x number of seconds (*1000 because clock reads in milliseconds).
      digitalWrite(input, HIGH); // turning pump off
    }

      count = 0; //reset values
      running_moisture_val_total = 0; //reset values
  }

  delay(600000); // delaying for 10 minute
  
 //Printing date time
//   Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(' ');
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
//    Serial.println();
//
//  //printing moisture value and watering information
//  Serial.print("Moisture Value: ");
//  Serial.print(soilMoistureValue);
//  Serial.println("");
//  Serial.print("Watering for: ");
//  Serial.print(((soilMoistureValue)/17.7) - 21.92);
//  Serial.println(" seconds.");
//  Serial.println("");
//  Serial.println("");

 // -------------------

// WATERING LOGIC 

// int waterDuration = 1000* ((soilMoistureValue/17.7) - 21.92); //water duration function - returns water amount based on soil moisture level.
//  
//   if(waterDuration < 1 )
//   
//     {
//      Serial.println("TOO WET! Negative water duration, not watering");
//     }
//   
//   else
//     {
//      digitalWrite(input, LOW); //turning pump on
//      delay(waterDuration); // pumping for x number of seconds.
//      digitalWrite(input, HIGH); // turning pump off
//      delay(60000); // delaying for 1 minute
//     }
  }
 // -------------------

      //    //SUPER DRY SOIL
      //    if(soilMoistureValue > superDryLevel)
      //    {
      //     Serial.println("Dry soil, adding water for 8 seconds.");
      //     digitalWrite(input, LOW); //turning pump on
      //     delay(8000);
      //     digitalWrite(input, HIGH); // turning pump off
      //     delay(60000);
      //    
      //      }
      //    
      //    //MEDIUM SOIL
      //     else if(soilMoistureValue < superDryLevel && soilMoistureValue > midLevel)
      //     {
      //      Serial.println("Medium soil, watering for 5 seconds.");
      //      digitalWrite(input, LOW); //turning pump on 
      //      delay(5000);
      //      digitalWrite(input, HIGH); // turning pump off
      //      delay(60000);
      //         
      //    }
      //    
      //    //WET SOIL
      //    else if(soilMoistureValue < midLevel)
      //    {
      //     Serial.println("Very Wet, Not watering");
      //      delay(5000);
      //    
      //    }
