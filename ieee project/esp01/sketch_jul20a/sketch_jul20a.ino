#include <ESP8266WiFi.h>
#include <WiFiClient.h>  
#include <string>

#define   SSD        "Hamdy Halim" 
#define   PASSWORD   "{A7med_H@mdy}"

#define  co2_id            49
#define  frame_id          50
#define  temprature_id     51
#define  FIRE_IS_DETECTED  52
#define  GAS_IS_DETECTED   53
#define  COUNTER_ID        54

WiFiServer server(80);

// char html_page[1000] = "<!DOCTYPE html><html><head> <title>ESP-01 Sensor Reading</title> <meta http-equiv=\"refresh\" content=\" 5; url=http://192.168.100.220 \" /> <meta charset=\" utf-8\"> </head><body onload=\"updateSensorReading()\"> <h1>ESP-01 temprature Sensor Reading:</h1> <div id=\"sensor-reading\"> %d </div><br><br><style>button{background-color: #4CAF50; /* Green */ border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; border-radius: 8px;}</style> <button onclick=\"changeUrl()\" > LED 1 ON </button> <button> LED 1 OFF</button><br><br><button>LED 2 ON </button> <button>LED 2 OFF </button><script></script></body></html>";
char html_page[4000] = "<!DOCTYPE html><html><head> <title>Embedded Heroes</title>  <meta http-equiv=\"refresh\" content=\" 5; url=http://192.168.43.128 \" /> <meta charset=\" utf-8\"> </head><body onload=\"updateSensorReading()\"> <style>body{background-color: #111; color: #fff; font-family: 'Roboto', Arial, sans-serif; text-align: center; line-height: 1.6; margin: 0;}header{background-color: #000000; color: #fff; padding: 20px; position: relative; overflow: hidden;}header h1{font-size: 36px; margin: 0; letter-spacing: 2px; font-weight: 600; text-transform: uppercase;}@keyframes headerBackgroundAnimation{0%{background-position: 0 0;}100%{background-position: 200% 0;}}@keyframes headerTextAnimation{0%{opacity: 0; transform: translateY(20px);}100%{opacity: 1; transform: translateY(0);}}header::before{content: \"\"; background: linear-gradient(135deg, #007bff, #00ccff, #33cc33, #ff6600); position: absolute; top: 0; left: 0; width: 100%; height: 100%; z-index: -1; animation: headerBackgroundAnimation 10s linear infinite;}header h1{animation: headerTextAnimation 1.5s ease-out;}main{margin: 20px; display: flex; flex-direction: column; align-items: center; justify-content: center; min-height: calc(100vh - 200px);}p{font-size: 24px; margin-bottom: 10px; position: relative;}#temp{font-weight: bold; color: #00ccff;}#co2{font-weight: bold; color: #33ff33;}#fire, #gas{font-weight: bold; color: #ccc; display: inline-block;}#fire:before{content: \"1f525\";}#gas:before{content: \"1f4a7\";}.floating{animation-name: floating; animation-duration: 3s; animation-iteration-count: infinite; animation-timing-function: ease-in-out;}@keyframes floating{0%{transform: translateY(0);}50%{transform: translateY(-30px);}100%{transform: translateY(0);}}@media screen and (max-width: 450px){header h1{font-size: 30px;}main{margin: 10px;}p{font-size: 18px;}.floating{animation-duration: 2s;}#temp, #co2, #fire, #gas{display: block;}#fire:before, #gas:before{font-size: 20px;}}</style></head><body> <header> <h1>Smart Home Secure</h1> </header> <main> <p class=\"floating\">The current temperature is <span id=\"temp\"> %d °C</span> and the CO2 level is <span id=\"co2\"> %d </span>.</p><p class=\"floating\"><<br><br><h1> People number = %d <\h1> </p></main></body></html>";
char temp_html_page[4000];
IPAddress IP;


void setup() {
   
  Serial.begin(9600);
  WiFi.disconnect(); /* it disconnect the old wifi in esp-01 */

  WiFi.mode(WIFI_STA);     /* I will make it station */
  WiFi.begin(SSD,PASSWORD);

  WiFi.setOutputPower(20.5);  /* To set the esp-01 with it's maximum wifi signal power */

   while( WiFi.status() != WL_CONNECTED )
   {
     delay(500);
   }

   Serial.println("\nconnected");
   Serial.print("IP : ");
   Serial.println( WiFi.localIP() );

   server.begin(); 


}


WiFiClient client ;
int co2_data = 0 ;
int frame_data = 0;
int temprature_data = 0;
int people_counter = 0;

//IFTT
const char host[] = "maker.ifttt.com";
const char key[] = "dGj_Fzx-YH4qD3SBigU08rBo3brB7Aa2Lh5hmTCpUhK";
const char event[] = "gas_detection";

const char key2[] = "dGj_Fzx-YH4qD3SBigU08rBo3brB7Aa2Lh5hmTCpUhK";
const char event2[] = "fire_detection";

int one = 1;

String fire = "" ;
String Gas =  "" ;

void loop() {
  // put your main code here, to run repeatedly:
  
  client = server.available();

    if( client )
    {
      /********************************************************************
        client.connected() is a method that returns true if the TCP connection is
        still open and both the client and server can still send and receive data. 
        If the connection has been closed by either the client or server,
        client.connected() will return false.

        client.available() is a method that returns the number of bytes available 
        to read from the remote server/client.
        If there is no data available to read, 
        client.available() will return 0.
      ********************************************************************/

     while( client.connected() && !client.available() )  /* if the client is connected, but the client didn't sent anything */
     {
        delay(1);
     }

     snprintf( temp_html_page , 4000 , html_page , temprature_data  , co2_data  , people_counter );

     
     if( client.available() ) /*If there is something to read*/
     {

     String req = client.readStringUntil('\r');  /* Take the GET request */
    //  Serial.println(req);

     int start_of_url = req.indexOf(' ') + 1 ;
     String URL = req.substring( start_of_url , req.indexOf(' ' , start_of_url ) );

     client.flush();
      // is a method in the Arduino WiFi library that is used to clear the outgoing buffer of a TCP connection between the ESP8266 module and a remote server/client. 

      if( URL == "/" )
      {  
         client.print(  temp_html_page );
      }

      if( one == 10 )
        {
          one = 0;
          
        }

      if( Serial.available() )
      {
        int id;
        id = Serial.read();

        if( id == co2_id )
        {
           co2_data = Serial.read();

        }else if( id == frame_id )
        {
          frame_data = Serial.read();
        }else if( id == temprature_id )
        {
           temprature_data = Serial.read();
        }else if( id == FIRE_IS_DETECTED )
        {
            fire = "Fire is detected" ;
            if( client.connect(host,80) )
             Serial.print("done");

            String host_url = "/trigger/";
            host_url = host_url + event2 + "/with/key/" + key2;

            String http = "GET " ;
            http = http + host_url + " HTTP/1.1\r\n";
            http = http + "Host: " + host + "\r\n";
            http = http + "Connection: close\r\n\r\n";

            client.print(http);
            Serial.print(http);

            client.stop();
        }else if( id == GAS_IS_DETECTED )
        {

             Gas = "Gas leakage is detected" ; 
             Serial.print("done");

            String host_url = "/trigger/";
            host_url = host_url + event + "/with/key/" + key;

            String http = "GET " ;
            http = http + host_url + " HTTP/1.1\r\n";
            http = http + "Host: " + host + "\r\n";
            http = http + "Connection: close\r\n\r\n";

            client.print(http);
            Serial.print(http);

            client.stop();
        }else if( id == COUNTER_ID )
        {
            people_counter = Serial.read();
        }

        


      } 

     

     }



    }

  


}









