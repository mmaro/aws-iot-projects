# AWS IoT AND AMAZON KINESIS PROJECTS

Projects using Amazon Web Services (AWS) including AWS IoT (Internet of Things),
Amazon Kinesis, and so on

## HomeSecure - Lowering Home Insurance Premium Using SMART HOME IoT SOLUTION

Smart home and automation is an internet of things solution for users to have
more control from preventing water leaks to air quality. It brings reliability
and intelligence to homes using AWS IoT services, applications and sensors.
Also, provides insurance and voice controlled features using Alexa Voice Services
and other AI services.

### Architecture

![image alt text](/images/HomeSecure_Arch_1.png)

### Hardware components used:

```
RedBot Buzzer
IC Hook with Pigtail
Arduino Uno - R3 SMD
Environmental Combo Breakout - CCS811/BME280
IC Hook Test Leads
Air Quality Breakout - CCS811
Adafruit BME280 I2C or SPI Temperature Humidity Pressure Sensor
Adafruit Ultimate GPS Breakout
USB 2.0 Cable - A-Male to B-Male
Echo Show
Resistors, 0 Ohm-1M Ohm
JBtek Breadboard Power Supply Module 3.3V/5V For Arduino Board
Breadboards
Water Sensor
PIR Pyroelectric IR Infrared Motion Sensor
Bluetooth 4.0 USB Module
Digital Buzzer Module
Push Button
LED
Adafruit Bluefruit LE SPI Friend - Bluetooth Low Energy (BLE)
Adafruit Bluefruit LE UART Friend - Bluetooth Low Energy (BLE)
Raspberry Pi 3
Gas Sensor
```

### Software and Cloud Services used:

```
AWS IoT Platform
Amazon Kinesis Firehose
Amazon Redshift for datawarehouse
Amazon S3 Object Storage
Amazon SNS
Amazon SES
Lambda
Weather API
Amazon SNS
IFTTT
Alexa Voice Service
Amazon Dynamo DB
Amazon Quicksight for Visualization
API Gateway
Arduino Sketch
Python, C, C++, Node/JS
```

### JSON PAYLOAD FROM DEVICE TO AWS CLOUD

```
{
   "co2":463,
   "temp":26.6,
   "pressure":99396.67,
   "leak":0,
   "gas":0.0,
   "longitude":-97.7174,
   "humidity":44,
   "motion":0,
   "latitude":30.3963,
   "tvoc":9,
   "at":"2017-11-27 17:20:10.472726",
   "gatewayid":"20-7a-b1-6b-d6",
   "sensorid":"20-7a-b1-00-d6-s3"
}

{
   "co2":463,
   "temp":26.6,
   "leak":0,
   "gas":0.0,
   "humidity":44,
   "motion":0,
   "pressure":99396.83,
   "tvoc":9,
   "at":"2017-11-27 17:20:13.594098",
   "gatewayid":"20-7a-b1-6b-d6",
   "sensorid":"20-7a-b1-00-d6-s3"
}
```

### RAW DATA

```
['latLocation', '30.3963', 'lonLocation', '-97.7174', 'watersensorvalue', '0', 'gas', '0.00', 'co2', '463', 'tvoc', '9', 'temp', '26.6', 'pressure', '99396.42', 'humidity', '44', 'pirmotiondat', '0']

['latLocation', '30.3963', 'lonLocation', '-97.7174', 'watersensorvalue', '0', 'gas', '0.00', 'co2', '463', 'tvoc', '9', 'temp', '26.6', 'pressure', '99396.67', 'humidity', '44', 'pirmotiondat', '0']

['watersensorvalue', '0', 'gas', '0.00', 'co2', '463', 'tvoc', '9', 'temp', '26.6', 'pressure', '99396.83', 'humidity', '44', 'pirmotiondat', '0']
```

### RAW DATA FROM GPS SATELLITES CAPTURED BY THE GPS SENSOR

```
Time: 18:37:56.984
Date: 26/11/2017
Fix: 1 quality: 1
Location: 3023.7705N, 9743.0361W
Location (in degrees, works with Google Maps): 30.3962, -97.7173
Speed (knots): 0.48
Angle: 165.66
Altitude: 220.10
Satellites: 9


Time: 18:36:54.0
Date: 26/11/2017
Fix: 1 quality: 1
Location: 3023.7761N, 9743.0400W
Location (in degrees, works with Google Maps): 30.3963, -97.7173
Speed (knots): 0.08
Angle: 34.55
Altitude: 219.70
Satellites: 8
```
## OTHER AWS IoT/ AMAZON KINESIS PROJECTS I AM WORKING ON

## 1.AIR QUALITY MONITORING IN SMART CITY USING WIRELESS SENSORS

In addition to discussions around reducing traffic congestion, easier access
to parking, monitoring and control of water quality, monitoring of air quality
is also a key element of a smart city which is also aimed at reducing levels
of greenhouse gases and combating global warming.

```
IC Hook with Pigtail
Arduino Uno - R3 SMD
Environmental Combo Breakout - CCS811/BME280
IC Hook Test Leads
Air Quality Breakout - CCS811
Adafruit Ultimate GPS Breakout
USB 2.0 Cable - A-Male to B-Male
Raspberry Pi 3
Amazon Echo
Android
Avnet Cellular Shield
AT&T IoT SIM Card
DFRobot Gravity: Laser PM2.5 Air Quality Sensor for Arduino
Waveshare Dust Sensor Detector
DFRobot Gravity: Laser PM2.5 Air Quality Sensor for Arduino
Honeywell HPMA115S0-XXX -  Gas Detection Sensor, PM2.5, Laser Scattering, Air,
```

## 2.REMOTE FUEL MONITORING

For diesel generators, fuel tanks, trucks and heavy machinery, the remote
fuel monitoring solution is a more accurate way to prevent losses, improve
operations cost and efficiency.

```
IC Hook with Pigtail
Arduino Uno - R3 SMD
Sparkfun Environmental Combo Breakout - CCS811/BME280
IC Hook Test Leads
Air Quality Breakout - CCS811
Adafruit Ultimate GPS Breakout
USB 2.0 Cable - A-Male to B-Male
Raspberry Pi 3
Amazon Echo
Avnet Cellular Shield
AT&T IoT SIM Card
Sierra Tools Battery-Operated Liquid Transfer Pump
Gas Can
Water Container
Ultrasonic Distance Sensor Module HC-SR04
DHT11 Digital Humidity Temperature Sensor
```

## 3.FLEET MONITORING SOLUTIONS / TRUCKING IoT

Fleet monitoring solution helps to provide insights from data collected from
electronic logging devices (ELDs) in cars and trucks and track drive times,
location, temperature, engine temperature, speed, and so on. Data is enriched
with weather data and other data in the device and in the AWS cloud.

## 3.1. SENDING TRUCK DATA TO AWS IoT

## Outline

-   [Prerequisites](#prerequisites)
-   [Quick, How Do I Use It?!](#quick-how-do-i-use-it)
-   [How It Works](#how-it-works)

## Prerequisites

-   An instance of the code is added to a directory on the Raspberry Pi.
-   Recent releases of Node and NPM packages are installed in the directory.
-   Get private key, private certificate and root certificate obtained by creating a representation of the device
-   in the AWS IoT management console or using AWS CLI

## Quick, How Do I Use It?!

In the directory for the sub-project, navigate the [Fleet Monitoring or Trucking IoT Sub-directory](https://github.com/mmaro/aws-iot-projects/tree/master/fleetMonitoring) of this project and then to truck js in the truckDataLogging folder and execute the command below:

```
node truck.js
```
Add private key, private certificate and root certificate to the same path as the truck js. Modify the path to the credentials in the script.

## How it Works

Developing ...

For an indepth look at the different components, check out the [Fleet Monitoring or Trucking IoT Wiki](#prerequisites).  For any questions or requests for more documentation, feel free to open an issue or fork this repo and contribute!

## 3.2 FOOD MATRIX - TRACING THE FOOD BACK TO THE SOURCE

Food matrix is an IoT Blockchain solution for food safety and audit, cold chain and food logistics. It leverages the hyperledger open source and free blockchain combined with AWS IoT.

Where is my food from?
Is it safe?

### FoodMatrix in Food Production and Supply Chain

![image alt text](/images/FoodMatrix_1.jpg)

In the directory for the sub-project, navigate the [Fleet Monitoring or Trucking IoT Sub-directory](https://github.com/mmaro/aws-iot-projects/tree/master/fleetMonitoring/foodmatrix) of this project and then to edgeclient js in the foodmatrix folder and execute the command below:

```
node edgeclient.js
```

Hardware components used:

```
Raspberry Pi 3

```

Software and Cloud Services used:

```
AWS IoT
Amazon EC2

```

## 3.3 Lowering Vehicle Insurance Premium Using ARITY Driving Behavior SDK AND AWS IoT

### Arity Driving Engine SDK

![image alt text](/images/Arity_DE_SDK.png)

### Driving Behavior using Arity SDK/API

![image alt text](/images/arity_driving_behavior.png)



## 4. Amazon FlightPulse, AWS IoT & Mobile Augmented Reality (AR)

### Hardware Setup

![image alt text](/images/rpi_sdr_nooelec.png)

Hardware components used:

```

Raspberry Pi 3
NooElec NESDR Mini 2+ 0.5PPM TCXO RTL-SDR & ADS-B USB Receiver - Software Defined Radio.
iPhone
iPad

```

Software and Cloud Services used:

```
AWS IoT
iOS
AWS Lambda
Amazon Kinesis
Weather APIs

```
