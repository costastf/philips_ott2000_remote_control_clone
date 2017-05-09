/*
  This code sends IR signals to a Philips OTT 2000.
  See the README file for more details.


   Copyright (C) 2017  Costas Tyfoxylos

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>
#include <IRremoteESP8266.h>

IRsend irsend(13); //an IR led is connected to GPIO pin 13 (D7)

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "NETWORK_SSID";
const char* password = "NETWORK_PASSWORD";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// The codes of the remote 
#define POWER           0x1140C   // Power button
#define SOURCE          0x143F    // Source button
#define DISPLAY         0x140F    // Display button
#define TUNING_LEFT     0x11421   // Tuning left button
#define TUNING_RIGHT    0x1420    // Tuning right button
#define PLAY_PAUSE      0x1142C   // Play-Pause button
#define ALT_PRESET_DOWN 0x1142B   // Alt-Preset Down button
#define ALT_PRESET_UP   0x142A    // Alt-Preset Up button
#define STOP            0x1431    // Stop button
#define SLEEP_TIMER     0x11026   // Sleep-Timer button
#define CLOCK_PROG      0x1444    // Clock-Prog button
#define PLAY_MODE       0x1141D   // Play-Mode button
#define FILE_CUT        0x1144C   // File-Cut button
#define REC             0x1446    // Rec button
#define INFO            0x11454   // Info button
#define VOLUME_DOWN     0x11411   // Volume Down button
#define VOLUME_UP       0x1410    // Volume Up button
#define MUTE            0x140D    // Mute button
#define SIGNAL_BIT_SIZE 20

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Declare functions to be exposed to the API
int send(String button);

void setup(void)
{
    // Start Serial
  Serial.begin(115200);
  delay(1000);
  
  // Start the infrared module
  irsend.begin();

  // Function to be exposed
  rest.function("send", send);

  // Give name & ID to the device
  rest.set_id("1");
  rest.set_name("Philips_OTT2000_Remote");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);

}

// Custom function accessible by the API
int send(String button) {
  button.toLowerCase();
  if (button == "power")
  {
    Serial.println("Sending POWER button");
    irsend.sendRC6(POWER, SIGNAL_BIT_SIZE);
  }
  else if (button == "source")
  {
    Serial.println("Sending SOURCE button");
    irsend.sendRC6(SOURCE, SIGNAL_BIT_SIZE);
  }
  else if (button == "display")
  {
    Serial.println("Sending DISPLAY button");
    irsend.sendRC6(DISPLAY, SIGNAL_BIT_SIZE);
  }
  else if (button == "tuning_left")
  {
    Serial.println("Sending TUNING_LEFT button");
    irsend.sendRC6(TUNING_LEFT, SIGNAL_BIT_SIZE);
  }
  else if (button == "tuning_right")
  {
    Serial.println("Sending TUNING_RIGHT button");
    irsend.sendRC6(TUNING_RIGHT, SIGNAL_BIT_SIZE);
  }
  else if (button == "play_pause")
  {
    Serial.println("Sending PLAY_PAUSE button");
    irsend.sendRC6(PLAY_PAUSE, SIGNAL_BIT_SIZE);
  }
  else if (button == "alt_preset_down")
  {
    Serial.println("Sending ALT_PRESET_DOWN button");
    irsend.sendRC6(ALT_PRESET_DOWN, SIGNAL_BIT_SIZE);
  }
  else if (button == "alt_preset_up")
  {
    Serial.println("Sending ALT_PRESET_UP button");
    irsend.sendRC6(ALT_PRESET_UP, SIGNAL_BIT_SIZE);
  }
  else if (button == "stop")
  {
    Serial.println("Sending STOP button");
    irsend.sendRC6(STOP, SIGNAL_BIT_SIZE);
  }
  else if (button == "sleep_timer")  
  {   
    Serial.println("Sending SLEEP_TIMER button");
    irsend.sendRC6(SLEEP_TIMER, SIGNAL_BIT_SIZE);
  }
  else if (button == "clock_prog")  
  {
    Serial.println("Sending CLOCK_PROG button");
    irsend.sendRC6(CLOCK_PROG, SIGNAL_BIT_SIZE);
  }
  else if (button == "play_mode")   
  { 
    Serial.println("Sending PLAY_MODE button");
    irsend.sendRC6(PLAY_MODE, SIGNAL_BIT_SIZE);
  }
  else if (button == "file_cut")   
  {    
    Serial.println("Sending FILE_CUT button");
    irsend.sendRC6(FILE_CUT, SIGNAL_BIT_SIZE);
  }
  else if (button == "rec")     
  {
    Serial.println("Sending REC button");
    irsend.sendRC6(REC, SIGNAL_BIT_SIZE);
  }
  else if (button == "info")   
  {
    Serial.println("Sending INFO button");
    irsend.sendRC6(INFO, SIGNAL_BIT_SIZE);
  }
  else if (button == "volume_down")   
  {
    Serial.println("Sending VOLUME_DOWN button");
    irsend.sendRC6(VOLUME_DOWN, SIGNAL_BIT_SIZE);
  }
  else if (button == "volume_up") 
  {
    Serial.println("Sending VOLUME_UP button");
    irsend.sendRC6(VOLUME_UP, SIGNAL_BIT_SIZE);
  }
  else if (button == "mute") 
  { 
    Serial.println("Sending MUTE button");
    irsend.sendRC6(MUTE, SIGNAL_BIT_SIZE);
  }
  else
  {
    Serial.println("Got an unknown button");
    Serial.println(button);
    return 1;
  }
    return 0;
}
