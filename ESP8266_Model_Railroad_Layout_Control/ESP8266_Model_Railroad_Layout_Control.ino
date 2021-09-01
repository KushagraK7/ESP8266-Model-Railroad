/*
 * Arduino code for controlling a model railroad layout with an ESP8266 using a browser on a device in local network.
 *
 * This example can control a locomotive and a turnout.
 *
 * You can add more turnouts and locomotive controls by modifying this and the PageIndex.h code.
 * 
 * Made by KushagraK7: https://www.instructables.com/member/KushagraK7/
 * 
 * The ESP8266 and the controlling device such as the laptop or the smartphone should be in the same local network.
 * 
 * 
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "PageIndex.h"; //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file

#define LEDonBoard 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router

//PWM outputs for locomotive's speed and direction control
#define OutA 14
#define OutB 12

//Digital outputs for turnout control
#define T1A 13
#define T1B 15

//----------------------------------------SSID and Password of your WiFi router
const char *ssid = "Router_SSID";
const char *password = "Router_Password";
//----------------------------------------

int p = 0;
int m = 1;
int sp;
float spe = 0;

String POS;
String Dir;
String TNo;
String TDir;

ESP8266WebServer server(80);  //--> Server on port 80

//----------------------------------------This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//----------------------------------------

//----------------------------------------Procedure for handling servo control
void setSpeed()
{
  POS = server.arg("POS");
  
  p = POS.toInt(); 
  
  Serial.print("Position:  ");
  Serial.print(p);
  Serial.print("  Direction:  ");
  Serial.println(m);
  server.send(200, "text/plane","");

  
}

void setDir()
{
  Dir = server.arg("Dir");

  if(Dir.length()  != 0) m = Dir.toInt();

  
  Serial.print("Position:  ");
  Serial.print(p);
  Serial.print("  Direction:  ");
  Serial.println(m);
  server.send(200, "text/plane","");
  
}

void setTNo()
{
  TNo = server.arg("TNo");
}

void setTDir()
{
  TDir = server.arg("TDir");

  turnout(TNo, TDir);

  Serial.print("Turnout ");
  Serial.print(TNo);
  Serial.print("'s direction: ");
  Serial.println(TDir);
}

void run(int s)
{
  if(s > 0 && s <= 255)
  {
    digitalWrite(OutB, LOW);
    analogWrite(OutA, s);
  }

  if(s < 0 && s >= -255)
  {
    digitalWrite(OutA, LOW);
    analogWrite(OutB, -s);
  }

  else
  {
    digitalWrite(OutB, LOW);
    digitalWrite(OutA, LOW);
  }

}

void turnout(String tNo, String tDir)
{

  if(tNo == "1")
  {
    if(tDir == "1")
    {
      digitalWrite(T1A, HIGH);
      delay(25);
      digitalWrite(T1A, LOW);
    }
  
    if(tDir == "0")
    {
      digitalWrite(T1B, HIGH);
      delay(25);
      digitalWrite(T1B, LOW);
    }
  }

}
//----------------------------------------
//----------------------------------------Setup----------------------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(OutA, OUTPUT);
  pinMode(OutB, OUTPUT);
  
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(LEDonBoard,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(LEDonBoard, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(LEDonBoard, LOW);
    delay(250);
    digitalWrite(LEDonBoard, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(LEDonBoard, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If connection is successful then show IP address in serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //----------------------------------------

  //----------------------------------------Initialize Webserver
  server.on("/",handleRoot);  //--> Routine to handle at root location. This is to display web page.
  server.on("/setPOS", setSpeed);
  server.on("/setDir", setDir);
  server.on("/setTNo", setTNo);
  server.on("/setTDir", setTDir);
  server.begin();  
  Serial.println("HTTP server started");
}
//------------------------------------------------------------------------------------
//----------------------------------------Loop----------------------------------------
void loop() {
 server.handleClient();

 sp = map(p, 0, 100, 0, 255);

 if(spe < sp*m) spe+= 0.1;
 if(spe > sp*m) spe-= 0.1;

 run(spe);
}
//------------------------------------------------------------------------------------
