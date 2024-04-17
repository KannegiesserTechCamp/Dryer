// external libraries 
#include <WiFi.h>
#include <uri/UriBraces.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ESPmDNS.h>

// internal includes
#include "LED.h"
#include "Dryer.h"

#define FILESYSTEM SPIFFS
// You only need to format the filesystem once
#define FORMAT_FILESYSTEM false

#if FILESYSTEM == FFat
#include <FFat.h>
#endif
#if FILESYSTEM == SPIFFS
#include <SPIFFS.h>
#endif

// ###########################################################################################################################################################
// ######################################################## WIFI SSID & PASSWORD #############################################################################
// ###########################################################################################################################################################
const char* ssid = "TechCamp"; // Enter your SSID here (Name of WIFI) 
const char* password = "Kannegiesser";  // Enter your Password here 

// local variables
const String left = "left";
const String right = "right"; 
const String stop = "stop";
const String led_switch_on = "on";
const String led_switch_off = "off";

bool led_status = 0;
String Motor = "stop";

AsyncWebServer server(80);  // Object of WebServer(HTTP port, 80 is default)

// website data (HTML, CSS + image paths)
#define PATH_TO_HTML "/techcamp.html"
#define PATH_TO_CSS "/design.css"
#define PATH_TO_LED_BUTTON_IMAGE "/LEDbutton.png"
#define PATH_TO_DRYER_BUTTON_IMAGE "/Trocknerbutton.png"
#define PATH_TO_LOGO_IMAGE "/logo.png"

String WebpageHTML;
String Css;

// open Filesystem 
bool exists(String path)
{
    bool does_exist = false;
    File file = FILESYSTEM.open(path, "r");
    
    if(!file.isDirectory())
    {
        does_exist = true;
    }
    
    file.close();
    return does_exist;
}


// ###########################################################################################################################################################
// ######################################################## REQUEST HANDLER ##################################################################################
// ###########################################################################################################################################################

// handle root url (/) 
// return html
void handle_root(AsyncWebServerRequest *request)
{
    if (exists(PATH_TO_HTML))
    {
        request->send(200, "text/html", WebpageHTML);
    }
    
    // if WebpageHTML not found 
    String htmlText = R"(
      <!DOCTYPE html>
      <html>
      <body>
      <h1>404</h1>
      <p>Sorry! &#128533; Inhalt ist nicht da und wahrscheinlich im Urlaub</p>
      </body>
      </html>
      )";

    request->send(404, "text/html", htmlText);
}

// return CSS
void handle_css(AsyncWebServerRequest *request)
{ 
    if (exists(PATH_TO_CSS))
    {
        request->send(200, "text/css", Css);
    }
}

// return LED button image
void handle_bannerLED(AsyncWebServerRequest *request)
{
    request->send(SPIFFS, PATH_TO_LED_BUTTON_IMAGE,"image/png");
}

// return dryer button image
void handle_bannerTrockner(AsyncWebServerRequest *request)
{
    request->send(SPIFFS, PATH_TO_DRYER_BUTTON_IMAGE,"image/png");
}

// return logo image
void handle_bannerLogo(AsyncWebServerRequest *request)
{
    request->send(SPIFFS, PATH_TO_LOGO_IMAGE,"image/png");
}

// return on error
void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

// ###########################################################################################################################################################
// ######################################################## ARDUINO STYLE SETUP ##############################################################################
// ###########################################################################################################################################################
void setup() {
  
    // start Serial Interface 
    Serial.begin(115200);
    
    // ###########################################################################################################################################################
    // ######################################################## LED and MOTOR SETUP ##############################################################################
    // ###########################################################################################################################################################
    // setup leds and motors
    ledsetup();
    Motorsetup();

    // ###########################################################################################################################################################
    // ######################################################## FILESYSTEM SETUP ##############################################################################
    // ###########################################################################################################################################################
    // Setup File Storage 
    if (FORMAT_FILESYSTEM)
    {
      Serial.println("Formating Filesystem");
      FILESYSTEM.format();
    }
    FILESYSTEM.begin();
    
    File root = FILESYSTEM.open("/");
    File file = root.openNextFile();
    Serial.println("Files on Filesystem:");
    
    while(file)
    {
        String fileName = file.name();
        Serial.println(fileName.c_str());
        file = root.openNextFile();
    }

    if (exists(PATH_TO_HTML))
    { 
        File file = SPIFFS.open(PATH_TO_HTML, "r");    
        WebpageHTML = file.readString();  
    }
    else
    {
        Serial.println("Couldn't find HTML file");
    }

    //CSS Pfad lesen 
    if (exists(PATH_TO_CSS)) 
    {
        File file = SPIFFS.open(PATH_TO_CSS, "r");    
        Css = file.readString();
    }
    else
    {
        Serial.println("Couldn't find CSS file");
    }
    
    // ###########################################################################################################################################################
    // ######################################################## WIFI SETUP ##############################################################################
    // ###########################################################################################################################################################
    Serial.println("Try Connecting to ");
    Serial.println(ssid);

    // Connect to your wi-fi modem
    WiFi.begin(ssid, password);

    // Check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());  //Show ESP32 IP on serial
    Serial.print("Got Mac-Adresse: ");
    Serial.println(WiFi.macAddress());

    // ###########################################################################################################################################################
    // ######################################################## LOAD WEBSITE DATA ##############################################################################
    // ###########################################################################################################################################################
    // handle HTMLpage with CSS
    server.on("/", HTTP_GET, handle_root);
    server.on("/design.css", HTTP_GET, handle_css);

    // handle images for webpage 
    server.on("/LEDbutton.png", HTTP_GET, handle_bannerLED);
    server.on("/Trocknerbutton.png", HTTP_GET, handle_bannerTrockner);
    server.on("/logo.png", HTTP_GET, handle_bannerLogo);

  // ###########################################################################################################################################################
    // ######################################################## MOTOR PATH ##############################################################################
    // ###########################################################################################################################################################
    // Motor path
    server.on("^\\/movement\\/(left|right|stop)$", HTTP_POST,  [](AsyncWebServerRequest *request)
    {
        String Move = request->pathArg(0);
        Serial.println(Move);
        request->send(201);
        
        // Check whether move is left
        if (Move == left)
        {
            if (Motor == "stopleft" || Motor == "stopright" || Motor == "stop" )
            {
                Motor = "motorLeft";
            }
            else if (Motor == "motorRight")
            {
                Motor = "stopright";
                delay(4000);
                Motor = "motorLeft";
            }
            Serial.println("move left");
        }
        // Check whether move is right
        else if (Move == right)
        {
            if (Motor == "stopleft" || Motor == "stopright" || Motor == "stop")
            {
                Motor = "motorRight";
            }
            else if (Motor == "motorLeft")
            {
                Motor = "stopleft";
                delay(4000);
                Motor = "motorRight";
            }
            Serial.println("move right");
        }
        // Check whether move is stop
        else if (Move == stop)
        {
            if (Motor == "motorRight")
            {
                Motor = "stopright";
                Serial.println("move will stop right");
            }
            else if (Motor == "motorLeft")
            {
                Motor = "stopleft";
                Serial.println("move will stop left");
            }
            else {
                Motor = "stop";
                Serial.println("motor is already stopped");
            }
        }
        else 
        {
            Serial.println("Could not find /movement/" + Move);
            request->send(404);
        }
    });

  // ###########################################################################################################################################################
    // ######################################################## LED PATH ##############################################################################
    // ###########################################################################################################################################################
    // LED path
    server.on("/light", HTTP_POST,  [](AsyncWebServerRequest *request)
    {
        request->send(201);

        if (led_status == 1)
        {
            led_status = 0;
            Serial.println("LED off");
        } 
        else
        {
            led_status = 1;
            Serial.println("LED on");
        }
    });

    server.onNotFound(notFound);

  // ###########################################################################################################################################################
    // ######################################################## SERVER START ##############################################################################
    // ###########################################################################################################################################################
    // go
    server.begin();
    Serial.println("HTTP server started");
    delay(100); 
  
    Serial.println();
    Serial.println("Running...");
}

// ### Arduino Loop Function ### 
// start loop 
void loop() {
  
    if (led_status == 1)
    {
        led_loop();
    }
    else if (led_status == 0)
    {
        led_off();
    }

    if (Motor == "motorRight")
    {
        MotorRight();
    }
    else if (Motor == "motorLeft")
    {
        MotorLeft();
    }
    else if (Motor == "stopleft")
    {
        MotorStopLeft();
    }
    else if (Motor == "stopright")
    {
        MotorStopRight();
    }
    else if (Motor = "stop")
    {
        MotorOff();
    }
}
