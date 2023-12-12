/* 
 * Project Serial1_Listener
 * Author: Chip McClelland  
 * Date: 12/12/2023
 * Description: This is a demo program to show how to use the Serial1_Listener class
 *
 */

//v1 - Initial version to send a simeple command to the Serial1 device and receive a response
//v2 - Added a function to set the threshold value on the Serial1 device


// Include Particle Device OS APIs
#include "Particle.h"
#include "Serial1_Listener.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

const pin_t ENABLE_PIN = D12;                 // Pin to enable the Serial1 device


// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);

// setup() runs once, when the device is first turned on
void setup() {
  Serial.begin(115200);                       // Open serial port to communicate with host          
  waitFor(Serial.isConnected, 10000);         // Wait here until the serial port is opened
  delay(1000);                                // Wait here for 1 second

  pinMode(ENABLE_PIN, OUTPUT);                // Set the ENABLE_PIN to output mode
  digitalWrite(ENABLE_PIN, LOW);             // Set the ENABLE_PIN to LOW to enable the Serial1 device

  Serial1_Listener::instance().setup();       // Setup the Serial1_Listener to listen to Serial1
}

void loop() {
  char response[256];                         // Where we will hold the response from the Serial1 device

  for (int i = 0; i < 6; i++) {               // Step through a series of 3 commands
    switch(i) {
      case 1:
        Log.info("Asking for Identification");      // Ask the Serial1 device for its identification
        Serial1.println("*IDN? \n");                // Send the *IDN? command to the Serial1 device
        if (Serial1_Listener::instance().getResponse(response, sizeof(response))) {   // Check if there is a response from the Serial1 device
          Log.info("Response: %s", response);       // Print the response from the Serial1 device
        }
        else {
          Log.info("No response from Serial1 device");
        }
        break;
      case 2:
        Log.info("Set the Threshold value");        // Ask the Serial1 device for the threshold value
        Serial1.println("CONF:THR 1.0 \n");           // Send the THRESHOLD? command to the Serial1 device
        if (Serial1_Listener::instance().getResponse(response, sizeof(response))) {   // Check if there is a response from the Serial1 device
          Log.info("Response: %s", response);       // Print the response from the Serial1 device
        }
        else {
          Log.info("Error setting Threshold value");
        }
        break;
      case 3:
        Log.info("Get the Threshold value");        // Ask the Serial1 device for the threshold value
        Serial1.println("CONF:THR? \n");           // Send the THRESHOLD? command to the Serial1 device
        if (Serial1_Listener::instance().getResponse(response, sizeof(response))) {   // Check if there is a response from the Serial1 device
          Log.info("Response: %s", response);       // Print the response from the Serial1 device
        }
        else {
          Log.info("No response for the Threshold value");
        }
        break;
      case 4:
        Log.info("Reset the Serial1 device");        // Ask the Serial1 device for the threshold value
        Serial1.println("*RESET \n");           // Send the THRESHOLD? command to the Serial1 device
        if (Serial1_Listener::instance().getResponse(response, sizeof(response))) {   // Check if there is a response from the Serial1 device
          Log.info("Response: %s", response);       // Print the response from the Serial1 device
        }
        else {
          Log.info("Failed to reset Serial1 device");
        }
        break;
      case 5:
        Log.info("End of the Demo");        // Ask the Serial1 device for the threshold value
        while(1);
        break;
    }
    delay(1000);                              // Wait here for 1 second
  }

}
