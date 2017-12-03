#!/usr/bin/python

import serial, string, time
import json
import ast
import datetime
import boto3
from picamera import PiCamera
from time import sleep
import authconfig as cfg

output = " "
ser = serial.Serial('/dev/ttyACM1', 115200, 8, 'N', 1, timeout=1)

iot = boto3.client('iot-data');

# Create an S3 client
s3 = boto3.client(
    's3',
    aws_access_key_id=cfg.myauth['ACCESS_KEY'],
    aws_secret_access_key=cfg.myauth['SECRET_KEY'],
    aws_default_region=cfg.myauth['AWS_DEFAULT_REGION']
)

# Call to S3 to retrieve the policy for the given bucket
result = s3.get_bucket_acl(Bucket='mikoaro-homesecure')
print(result)


def getserial():
  # Extract serial from cpuinfo file
  cpuserial = "0000000000000000"
  try:
    f = open('/proc/cpuinfo','r')
    for line in f:
      if line[0:6]=='Serial':
        cpuserial = line[10:26]
    f.close()
  except:
    cpuserial = "ERROR000000000"

  return cpuserial

def camera():
    camera = PiCamera()
    camera.start_preview()
    camera.sleep(1)
    camera.capture('/home/pi/Desktop/image.jpg')
    camera.stop_preview()

while True:
  print "----"
  while output != "":
    output = ser.readline()
    print output
    arrOutput = output.split(',')
    print arrOutput
    if ( len(arrOutput) > 13 and (arrOutput[1] == 'watersensorvalue' or arrOutput[1] == 'latLocation')):
      print('good stuff')
      arrOutput.pop(0)
      arrOutput = arrOutput[:-1]
      print arrOutput
      iotdata = {}
      if'0.00ersensorvalue' in arrOutput:
        continue
      if '41ure' in arrOutput:
        continue
      if 'latLocation' in arrOutput:
        iotdata["sensorid"] = "20-7a-b1-00-d6-s3"
        iotdata["gatewayid"] = "20-7a-b1-6b-d6"
        iotdata["latitude"] = ast.literal_eval(arrOutput[arrOutput.index('latLocation') + 1])
        iotdata["longitude"] = ast.literal_eval(arrOutput[arrOutput.index('lonLocation') + 1])
        iotdata["gas"] = ast.literal_eval(arrOutput[arrOutput.index('gas') + 1])
        iotdata["leak"] = ast.literal_eval(arrOutput[arrOutput.index('watersensorvalue') + 1])
        iotdata["temp"] = ast.literal_eval(arrOutput[arrOutput.index('temp') + 1])
        iotdata["pressure"] = ast.literal_eval(arrOutput[arrOutput.index('pressure') + 1])
        iotdata["humidity"] = ast.literal_eval(arrOutput[arrOutput.index('humidity') + 1])
        iotdata["motion"] = ast.literal_eval(arrOutput[arrOutput.index('pirmotiondat') + 1])
        iotdata["co2"] = ast.literal_eval(arrOutput[arrOutput.index('co2') + 1])
        iotdata["tvoc"] = ast.literal_eval(arrOutput[arrOutput.index('tvoc') + 1])
        iotdata["at"] = str(datetime.datetime.utcnow())
        jsoniotdata = json.dumps(iotdata)
        print jsoniotdata
        response = iot.publish(
             topic='/homesecure/devicedata',
             payload=jsoniotdata
        )
      else:
        iotdata["sensorid"] = "20-7a-b1-00-d6-s3"
        iotdata["gatewayid"] = "20-7a-b1-6b-d6"
        iotdata["gas"] = ast.literal_eval(arrOutput[arrOutput.index('gas') + 1])
        iotdata["leak"] = ast.literal_eval(arrOutput[arrOutput.index('watersensorvalue') + 1])
        iotdata["temp"] = ast.literal_eval(arrOutput[arrOutput.index('temp') + 1])
        iotdata["pressure"] = ast.literal_eval(arrOutput[arrOutput.index('pressure') + 1])
        iotdata["humidity"] = ast.literal_eval(arrOutput[arrOutput.index('humidity') + 1])
        iotdata["motion"] = ast.literal_eval(arrOutput[arrOutput.index('pirmotiondat') + 1])
        iotdata["co2"] = ast.literal_eval(arrOutput[arrOutput.index('co2') + 1])
        iotdata["tvoc"] = ast.literal_eval(arrOutput[arrOutput.index('tvoc') + 1])
        iotdata["at"] = str(datetime.datetime.utcnow())
        jsoniotdata = json.dumps(iotdata)
        print jsoniotdata
        response = iot.publish(
             topic='/homesecure/devicedata',
             payload=jsoniotdata
        )
        print('serial')
        myserial = getserial()
        print myserial
   # time.sleep(1)
  output = " "
