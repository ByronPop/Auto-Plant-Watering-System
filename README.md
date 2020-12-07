# Arduino Automatic Plant Watering System


## Introduction

During the depths of March Rona quarantine, I decided to make an automatic plant watering system with the Arduino board I had from college. 
While it took a little while to figure out, the system now monitors the soil moisture level, records the measurements to an SD card, and waters the plant according
to a simple model I created. By tuning the watering model I have been able to reduce the variability in the soil moisture,  decreasing the standard deviation in weekly moisture readings from ~12.5 at the start to ~6 as of the last weekly test. Here's how the system works. 

![IMG_1033](https://user-images.githubusercontent.com/33380363/101300559-fddb5800-3803-11eb-8e5c-2bd2ec7471b0.JPG)

## Components 

The watering system is made up the following components:
* Arduino board
* Soil moisture sensor
* 12V peristaltic water pump
* 12V external power supply
* 5V relay
* Micro SD card reader 
* RTC clock module
* Breadboard
* Wiring

## Wiring Diagram

Below is a wiring diagram showing how the different parts. The circuito.io diagram with parts can be seen [here](https://www.circuito.io/static/reply/index.html?solutionId=5fcd85eab1558400300adb81&solutionPath=storage.circuito.io).  all In the next section I will describe in words how it works. 

<img width="801" alt="Screen Shot 2020-12-06 at 8 49 15 PM" src="https://user-images.githubusercontent.com/33380363/101301377-a8ed1100-3806-11eb-9548-59c4a4611fc8.png">



## How It Works












![IMG_1034](https://user-images.githubusercontent.com/33380363/101300567-03d13900-3804-11eb-849b-2f55a9cbd76b.JPG)
