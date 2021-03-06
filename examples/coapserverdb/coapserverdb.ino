/*
  ESP-COAP Server
*/
#include <ESP8266WiFi.h>
#include "coap_server.h"
// CoAP server endpoint url callback
void callback_light(coapPacket &packet, IPAddress ip, int port, int obs);

coapServer coap;
coapServer co; //test

//WiFi connection info
const char* ssid = "yui";
const char* password = "guessyui";

// LED STATE
bool LEDSTATE;

// CoAP server endpoint URL
void callback_light(coapPacket *packet, IPAddress ip, int port, int obs) {
  Serial.println("light");
  
  // send response
  char p[packet->payloadlen + 1];
  memcpy(p, packet->payload, packet->payloadlen);
  p[packet->payloadlen] = NULL;
 // Serial.println(p);
  Serial.println(p);
  String message(p); //tbd
  //Serial.println(p);192
//  if (message.equals("0"))
//  {
//    digitalWrite(16, LOW);
//    Serial.println("if loop");
//  }
//  else if (message.equals("1"))
//  {
//    digitalWrite(16, HIGH);
//    Serial.println("else loop");
//  }
//  //char *light;
int rand = random(0,100);
char light[16];
itoa(rand, light, 10);
//sprintf(light[], "%04d", rand);
//  randnum.toCharArray(light,10);
  
  //char light[] = "test";//(digitalRead(16) > 0) ? ((char *) "1") : ((char *) "0");      // send a text file.
  Serial.println(light);

  //coap.sendResponse(packet, ip, port, light);
  if (obs == 1)
    coap.sendResponse(light);
  else
    coap.sendResponse(ip, port, light);
}

//void callback_lightled(coapPacket *packet, IPAddress ip, int port, int obs) {
//  Serial.println("Lightled");
//
//  // send response
//  char p[packet->payloadlen + 1];
//  memcpy(p, packet->payload, packet->payloadlen);
//  p[packet->payloadlen] = NULL;
//
//  String message(p);
//
//  if (message.equals("0"))
//    LEDSTATE = false;
//  else if (message.equals("1"))
//    LEDSTATE = true;
//
//  if (LEDSTATE) {
//    digitalWrite(2, HIGH) ;
//    if (obs == 1)
//      coap.sendResponse("1");
//    else
//      coap.sendResponse(ip, port, "1");
//
//    //coap.sendResponse("1");
//  } else {
//    digitalWrite(2, LOW) ;
//    if (obs == 1)
//      coap.sendResponse("0");
//    else
//      coap.sendResponse(ip, port, "0");
//    //coap.sendResponse("0");
//  }
//}


void setup() {
  yield(); //delay :
//  serial begin
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println(" ");

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //    yield();
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());

  // LED State
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  LEDSTATE = true;

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  //LEDSTATE = true;


  // add server url endpoints.
  // can add multiple endpoint urls.

    coap.server(callback_light, "light");
//    coap.server(callback_lightled, "lightled");
  // coap.server(callback_text,"text");

  // start coap server/client
  coap.start();
  coap.start(5683);
}

void loop() {
  coap.loop();
  //  delay(1000);


}
