# Arduino Automatic Plant Watering System
An Arduino powered automatic plant watering system

## Introduction

During the depths of the March pandeminc, I decided to make an automatic plant watering system with the Arduino board I had from college. 
While it took a little while to figure out, the system now monitors the soil moisture level, records the measurements to an SD card, and waters the plant according to a simple model I created. By tuning the watering model I have been able to reduce the variability in the soil moisture,  decreasing the standard deviation in weekly moisture readings from ~12.5 at the start to ~6 as of the last weekly test. Most important of all the plant is THRIVING! Here's how the system works. 

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

Below is a wiring diagram showing how the different parts. The circuito.io diagram with parts can be seen [here](https://www.circuito.io/static/reply/index.html?solutionId=5fcd85eab1558400300adb81&solutionPath=storage.circuito.io). See the attached .ino file for the associated program code. 

<img width="801" alt="Screen Shot 2020-12-06 at 8 49 15 PM" src="https://user-images.githubusercontent.com/33380363/101301377-a8ed1100-3806-11eb-9548-59c4a4611fc8.png">


## How It Works

The watering system is a mix of inputs and outputs. First, the moisture sensor reads the soil moisture level and returns a number corresponding to how wet or dry the soil is. The data is then written to the SD card module along with a date/time measurement. The system performs this process every minute. Every hour, the system takes the average of the prior 60 moisture readings and inputs it into a model that determine how long to water the plant. The system uses an average in order to mitigate any single erroneous measurement. A signal then triggers the 5V relay attached to the Arduino to power the 12V water pump for the duration of time specified by the model. This monitoring and watering process continues 24/7. 

![IMG_1033](https://user-images.githubusercontent.com/33380363/101300559-fddb5800-3803-11eb-8e5c-2bd2ec7471b0.JPG)


## Tuning the Model

The watering model takes the input from the soil moisture sensor and outputs a watering time. Soil moisture values range from ~300 (very wet) to ~750 (very dry). I used a linear model to calculate watering duration. Based on the data, I tweaked the model to administer more or less water (slope). The final model (v5) used the following equation: (Avergage Soil Moisture/20) - 25. By tuning the watering model I have been able to reduce the variability in the soil moisture,  decreasing the standard deviation in weekly moisture readings from ~12.5 at the start to ~6 as of the last weekly test.

v1            |  v5
:-------------------------:|:-------------------------:
![Screen Shot 2020-12-07 at 8 02 23 AM](https://user-images.githubusercontent.com/33380363/101354072-9274a300-3862-11eb-9d32-59b24aafafcb.png)|![Screen Shot 2020-12-07 at 8 32 55 AM](https://user-images.githubusercontent.com/33380363/101357020-e1243c00-3866-11eb-8e07-af0559232fe7.png)


