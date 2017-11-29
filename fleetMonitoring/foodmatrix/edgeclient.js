var awsIot = require('aws-iot-device-sdk');

const aws = require('aws-sdk');

const config = require('config');

//var config = require("./device.json");

// Key Path is the path to the private key
const KEY_PATH = (process.env.EDGE_DEVICE_PRIVATE_KEY) ?
  process.env.EDGE_DEVICE_PRIVATE_KEY :
  config.get('keyPath');

// Cert Path is the path to the private certificate
const CERT_PATH = (process.env.EDGE_DEVICE_CERTIFICATE) ?
  process.env.EDGE_DEVICE_CERTIFICATE :
  config.get('certPath');

// Client ID
const CLIENT_ID = (process.env.CLIENT_ID) ?
  process.env.CLIENT_ID :
  config.get('clientId');

// ROOT CA Path is the path to the root CA
const ROOT_CA = (process.env.ROOT_CA) ?
  process.env.ROOT_CA :
  config.get('caPath');

// Interact REST Endpoint
 const HOST = (process.env.HOST) ?
  process.env.HOST :
  config.get('host');


var device = awsIot.device({
  keyPath: KEY_PATH,
  certPath: CERT_PATH,
  caPath: ROOT_CA,
  clientId: CLIENT_ID,
  host: HOST
});


//Data array for blockchain data payload
var longitude = [-98.49,-97.74,-96.79,-94.20,-90.19,-94.57,-87.62,-87.90,-93.26,-95.99];
var latitude  = [29.42,30.26,32.77,36.37,38.62,39.09,41.87,43.03,44.97,41.25];
var temperature = [21,22,23,24,25,26,27,28,29,30];
var carrier = ["CARRIER-1","CARRIER-2","CARRIER-3","CARRIER-4","CARRIER-5","CARRIER-6","CARRIER-7","CARRIER-8","CARRIER-9","CARRIER-10"];
var index = -1;


function generatePayload( ) {

 if ( index >= 9 )
   index = 0;
 else
   index++

var param = {
   d:{
      "assetID":"EDGE-ASSET-01",
      "location":{
         "longitude":longitude         [
            index
         ],
         "latitude":latitude         [
            index
         ]
      },
      "temperature":temperature      [
         index
      ],
      "carrier":carrier      [
         index
      ]
   }
}

return param;

}

//
// Device is an instance returned by mqtt.Client(), see mqtt.js for full
// documentation.
//
device
  .on('connect', function() {
    var i=0;
    console.log("connected");

    setInterval(function function_name () {
            i++;
            device.publish('carrier/devicedata', JSON.stringify(generatePayload( )));
            console.log('\n Publishing:\n', JSON.stringify(generatePayload( )));
    },2000);

  });

  device
    .on('message', function(topic, payload) {
      console.log('message', topic, payload.toString());
    });

  device
     .on('close', function() {
        console.log('close');
      });
  device
     .on('reconnect', function() {
        console.log('reconnect');
      });
  device
     .on('offline', function() {
        console.log('offline');
      });
  device
     .on('error', function(error) {
        console.log('error', error);
      });
