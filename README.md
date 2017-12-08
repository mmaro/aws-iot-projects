# AWS IoT AND AMAZON KINESIS PROJECTS

Projects using Amazon Web Services (AWS) including AWS IoT (Internet of Things),
Amazon Kinesis, and so on

## Project Introduction: HomeSecure and Homeowner’s Insurance - IoT and SMART HOME SOLUTION for Insurers

HomeSecure for insurers is an internet of things smart home and automation solution for users to have more control from preventing water leaks to air quality. It brings reliability and intelligence to homes using AWS IoT services, applications and sensors. Also, provides insurance and voice controlled features using Alexa Voice Services and other AI services. The IoT solution also helps insurance companies to better relate with their customers. It provides an opportunity for an insurance company to move from being passive and reacting to losses to helping prevent them.

In the connected home, devices and sensors generate a lot of data that are refined and exploited. This data is particularly important to insurers who have traditionally based their pricing on risk assessment. HomeSecure offers better data on which to base judgements by insurers. HomeSecure would give insurers a more direct relationship with the consumer through daily interaction using touch points in apps and messaging. Insurers also become more competitive by adopting pricing strategies that include direct sourcing and bundling with policies.

By partnering with IoT companies, insurers can leverage technologies such as connected water leakage detectors and temperature sensors to continuously monitor customers’ homes. These technologies provide homeowners with early warning signs and the ability to act quickly in the case of an adverse event, allowing insurers to better mitigate risks and reduce losses for customers.

Reading and hearing about the home security stories of others in the neighborhood can be what is needed to invest in one's home or rental apartment. What's the fun in buying home security gadgets and not building a single one for oneself while utilizing AWS IoT platform, Amazon Kinesis and other services for IoT data management, processing and analytics given a free-tier account and a free credit?

It is very essential to protect one's home against fire, intruders, flood or water leak, and so on. It will bring about self defense and peace of mind and if not prevent or minimize the damage.

### Hardware components used:


- RedBot Buzzer
- IC Hook with Pigtail
- Arduino Uno - R3 SMD
- Environmental Combo Breakout - CCS811/BME280
- IC Hook Test Leads
- Air Quality Breakout - CCS811
- Adafruit BME280 I2C or SPI Temperature Humidity Pressure Sensor
- Adafruit Ultimate GPS Breakout
- USB 2.0 Cable - A-Male to B-Male
- Echo Show
- Resistors, 0 Ohm-1M Ohm
- JBtek Breadboard Power Supply Module 3.3V/5V For Arduino Board
- Breadboards
- Water Sensor
- PIR Pyroelectric IR Infrared Motion Sensor
- Bluetooth 4.0 USB Module
- Digital Buzzer Module
- Push Button
- LED
- Adafruit Bluefruit LE SPI Friend - Bluetooth Low Energy (BLE)
- Adafruit Bluefruit LE UART Friend - Bluetooth Low Energy (BLE)
- Raspberry Pi 3
- Gas Sensor
- Raspberry Pi Camera
- Raspberry Pi Camera Module Mount


### Software and Cloud Services used:

- AWS IoT Platform
- Amazon Kinesis Firehose
- Amazon Redshift for datawarehouse
- Amazon S3 Object Storage
- Amazon SNS
- Amazon SES
- Lambda
- Weather API
- Amazon SNS
- IFTTT
- Alexa Voice Service
- Amazon Dynamo DB
- Amazon Quicksight for Visualization
- API Gateway
- Arduino Sketch
- Python, C, C++, Node/JS


### Architecture

![image alt text](/images/HomeSecure_Arch_1.png)


### System Overview

We need a Raspberry Pi and Arduino UNO as well as sensors. The devices can be placed anywhere in the home to measure. Data collected from the HomeSecure monitor is sent directly to AWS IoT, where the data can be displayed and analyzed using Amazon Kinesis and other Amazon web services.

![image alt text](/images/arduino_uno_sensors_0.png)

Sensor data is acquired using an Arduino UNO. From there, data is packaged and sent to a Raspberry Pi via a serial connection, external to the enclosure. The Raspberry Pi acts as the connection gateway and publishes the packaged data to AWS IoT. For immediate purposes data flow is unidirectional, meaning the unit is not subscribing to any outside streams, though this could easily be integrated.

![image alt text](/images/rpi_wt_camera_0.png)


For an indepth look at the different components, in the directory for the sub-project, navigate the [smartHome Security and Automation Sub-directory](https://github.com/mmaro/aws-iot-projects/tree/master/smartHomeSecurityAndAutomation) of this project.

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

### AWS IoT Data source

Running the HomeSecureApp.py Python script while connected to the Arduino UNO will publish real live messages to the AWS IoT platform from the devices. The IoT rule sends the message to Firehose for further processing.

The script requires access to AWS CLI credentials and boto3 installation on the machine running the script. Download and run the following Python script after setting up the data collection and data transmission systems of HomeSecure:

https://github.com/mmaro/aws-iot-projects/blob/master/smartHomeSecurityAndAutomation/smartHomeSecurity/sense_your_home/rpi/HomeSecureApp.py

In the absence of a physical device, sample data can be also generated from the JSON payload for experimenting with IoT, Streams and Visualization.

### Use Case, Business Imperative, and Amazon Kinesis Firehose delivery streams

An insurer or user would like to see and analyze a trend of 5 minutes worth of data. The use case requires that water leak sensor/value be dry. The ideal thresholds for temperature ranges from a minimum of 10 to a maximum of 38 degree celsius. For indoor air quality, the ideal condition for indoor relative humidity for health and comfort can be set to about 40-50%. In the winter months, it may have to be lower than 40% RH. For this use case, an ideal condition for indoor relative humidity is any value above the minimum of 33 and up to 50%. When conditions are outside ideal ranges, several issues arise:

- Temperature greater than 38°C (100°F).
- Temperature below 10°C (50°F).
- An RH less than 33 promotes condensation on the windows, visible mold growth in your home, basement, and/or crawl space, peeling wallpaper/blistering paint, allergic reactions to mold and/or dust mites, a musty odor in your home, and/or basement and crawl space or cupped wood floors.
- Water leak becomes wet promotes flooding of the kitchen, laundry, beach house 3rd floor or any other places.

Alarms (rules) are activated for conditions that are outside the ideal ranges as stated above.

There are more details about the setup for Kinesis and Quicksight in this [similar project](https://aws.amazon.com/blogs/big-data/build-a-visualization-and-monitoring-dashboard-for-iot-data-with-amazon-kinesis-analytics-and-amazon-quicksight/) : Build a Visualization and Monitoring Dashboard for IoT Data with Amazon Kinesis Analytics and Amazon QuickSight.


### Create four Firehose delivery streams

1. Open the **Kinesis Firehose** console at https://console.aws.amazon.com/firehose/
2. Create all four Firehose delivery streams by choosing the **Create Delivery Stream** button. Follow the steps in the wizard and choose the default settings. The default **buffer interval** is set to 300 seconds i.e. 5 minute-window for trend analysis according to our use case above. Use the fields and values in the tables below. Choose the **firehose_delivery_role** IAM role.

**Delivery stream 1:**

|Field                  | Value
|:---                   |:---
|Name                   | IoT-Source-Stream
|S3 bucket              | [your unique name here]-kinesis
|S3 prefix              | source/

**Delivery stream 2:**

|Field                  | Value
|:---                   |:---
|Name                   | IoT-Destination-Data-Stream
|S3 bucket              | [your unique name here]-kinesis
|S3 prefix              | data/

**Delivery stream 3:**

|Field                  | Value
|:---                   |:---
|Name                   | IoT-Destination-Aggregate-Temp-Stream
|S3 bucket              | [your unique name here]-kinesis
|S3 prefix              | aggregate-temp/

**Delivery stream 4:**

|Field                  | Value
|:---                   |:---
|Name                   | IoT-Destination-Aggregate-Humidity-Stream
|S3 bucket              | [your unique name here]-kinesis
|S3 prefix              | aggregate-humidity/



## OTHER AWS IoT/ AMAZON KINESIS PROJECTS I AM WORKING ON

## 1.AIR QUALITY MONITORING IN SMART CITY USING WIRELESS SENSORS

In addition to discussions around reducing traffic congestion, easier access
to parking, monitoring and control of water quality, monitoring of air quality
is also a key element of a smart city which is also aimed at reducing levels
of greenhouse gases and combating global warming.

- IC Hook with Pigtail
- Arduino Uno - R3 SMD
- Environmental Combo Breakout - CCS811/BME280
- IC Hook Test Leads
- Air Quality Breakout - CCS811
- Adafruit Ultimate GPS Breakout
- USB 2.0 Cable - A-Male to B-Male
- Raspberry Pi 3
- Amazon Echo
- Android
- Avnet Cellular Shield
- AT&T IoT SIM Card
- DFRobot Gravity: Laser PM2.5 Air Quality Sensor for Arduino
- Waveshare Dust Sensor Detector
- DFRobot Gravity: Laser PM2.5 Air Quality Sensor for Arduino
- Honeywell HPMA115S0-XXX -  Gas Detection Sensor, PM2.5, Laser Scattering, Air,

## 2.REMOTE FUEL MONITORING

For diesel generators, fuel tanks, trucks and heavy machinery, the remote
fuel monitoring solution is a more accurate way to prevent losses, improve
operations cost and efficiency.

- IC Hook with Pigtail
- Arduino Uno - R3 SMD
- Sparkfun Environmental Combo Breakout - CCS811/BME280
- IC Hook Test Leads
- Air Quality Breakout - CCS811
- Adafruit Ultimate GPS Breakout
- USB 2.0 Cable - A-Male to B-Male
- Raspberry Pi 3
- Amazon Echo
- Avnet Cellular Shield
- AT&T IoT SIM Card
- Sierra Tools Battery-Operated Liquid Transfer Pump
- Gas Can
- Water Container
- Ultrasonic Distance Sensor Module HC-SR04
- DHT11 Digital Humidity Temperature Sensor


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

For an indepth look at the different components, check out the [Fleet Monitoring or Trucking IoT Wiki](#prerequisites).  For any questions or requests for more documentation, feel free to open an issue or fork this repo and contribute!

## 3.2 FOOD MATRIX - TRACING THE FOOD BACK TO THE SOURCE

Food matrix is an IoT Blockchain solution for food safety and audit, cold chain and food logistics. It leverages the hyperledger open source and free blockchain combined with AWS IoT.

- Where is my food from?
- Is it safe?

### FoodMatrix in Food Production and Supply Chain

![image alt text](/images/FoodMatrix_1.jpg)

In the directory for the sub-project, navigate the [Fleet Monitoring or Trucking IoT Sub-directory](https://github.com/mmaro/aws-iot-projects/tree/master/fleetMonitoring/foodmatrix) of this project and then to edgeclient js in the foodmatrix folder and execute the command below:

```
node edgeclient.js
```

### Hardware components used:

- Raspberry Pi 3

### Software and Cloud Services used:

- AWS IoT
- Amazon EC2


## 3.3 Lowering Vehicle Insurance Premium Using ARITY Driving Behavior SDK AND AWS IoT

### Arity Driving Engine SDK

![image alt text](/images/Arity_DE_SDK.png)

### Driving Behavior using Arity SDK/API

![image alt text](/images/arity_driving_behavior.png)



## 4. Amazon FlightPulse, AWS IoT & Mobile Augmented Reality (AR)

### Architecture

![image alt text](/images/rpi_sdr_Arch_1.png)

### Hardware Setup

![image alt text](/images/rpi_sdr_nooelec.png)


### Hardware components used:

- Raspberry Pi 3
- NooElec NESDR Mini 2+ 0.5PPM TCXO RTL-SDR & ADS-B USB Receiver - Software Defined Radio.
- iPhone
- iPad


### Software and Cloud Services used:

- AWS IoT
- iOS
- AWS Lambda
- Amazon Kinesis
- Weather APIs
