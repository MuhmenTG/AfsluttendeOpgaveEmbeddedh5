#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an HTTP request ends with a blank line
    bool currentLineIsBlank = true;
    if (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
         client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
           
            
 
           // HTML web page to handle 2 input fields (input1, input2)
            const char index_html[] PROGMEM = R"rawliteral(
                <!DOCTYPE html>
                <html>
                <style>
                input[type=text], select {
                  width: 100%;
                  padding: 12px 20px;
                  margin: 8px 0;
                  display: inline-block;
                  border: 1px solid #ccc;
                  border-radius: 4px;
                  box-sizing: border-box;
                }

                input[type=submit] {
                  width: 100%;
                  background-color: #4CAF50;
                  color: white;
                  padding: 14px 20px;
                  margin: 8px 0;
                  border: none;
                  border-radius: 4px;
                  cursor: pointer;
                }

                input[type=submit]:hover {
                  background-color: #45a049;
                }

                div {
                  border-radius: 5px;
                  background-color: #f2f2f2;
                  padding: 20px;
                }
                </style>
                <body>

                <h3>Varmestyringsanl&aelig;g</h3>

                <div>
                  <form action="/action_page.php">
                    <label for="fname">Indtast temperatur</label>
                    <input type="text" id="tempValue" name="tempValue">

                                   
                    <input type="submit" value="Bekr&aelig;ft temperatur">

                    <label for="lname">Indtast komfort temperatur</label>
                    <input type="text" id="comfortTempValue" name="comfortTempValue">

                     <label for="lname">Indtast spare temperatur</label>
                    <input type="text" id="savingTempValue" name="savingTempValue">

                  
                    <input type="submit" value="Bekr&aelig;ft komfort- og sparetemperatur">
                  </form>
                </div>
                <br>
              </form><br>
            </body></html>)rawliteral";
 
            client.println(index_html);

        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop(); 
  }
}