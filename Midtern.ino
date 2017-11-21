#include <LWiFi.h>
//燈泡Set-up
#define GreenPin 8
#define BluePin 7
#define RedPin 6

char ssid[] = "AndroidAP0144";      //  your network SSID (name)
char pass[] = "pdfh6278";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
long randNumber;
int correct=0;
int status = WL_IDLE_STATUS;
WiFiServer server(80);


void setup() {
  Serial.begin(9600);      // initialize serial communication

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
  
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(17, INPUT);
  pinMode(16, INPUT);
  pinMode(15, INPUT);
}


void loop() {
  randNumber = random(1000)%3;
   switch(randNumber) 
   {
    case 0: digitalWrite(GreenPin, HIGH);digitalWrite(BluePin, LOW); digitalWrite(RedPin, LOW); break;
    case 1: digitalWrite(GreenPin, LOW);digitalWrite(BluePin, HIGH); digitalWrite(RedPin, LOW); break;
    case 2: digitalWrite(GreenPin, LOW);digitalWrite(BluePin, LOW); digitalWrite(RedPin, HIGH); break;
   }
   
   int greenstatus=digitalRead(17);
   int bluestatus=digitalRead(16);
   int redstatus=digitalRead(15);
   

   delay(1000);
   if(greenstatus== HIGH && bluestatus== LOW && redstatus== LOW && randNumber==0) correct++;
   if(greenstatus== LOW && bluestatus== HIGH && redstatus== LOW && randNumber==1) correct++;
   if(greenstatus== LOW && bluestatus== LOW && redstatus== HIGH && randNumber==2) correct++;

    greenstatus=LOW;
    redstatus=LOW;
    bluestatus=LOW;
    
  WiFiClient client = server.available();   // listen for incoming clients

    if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          client.println("<head>\n");
          client.println("<meta charset='UTF-8'/>\n");
          client.println("<title>Playing Hamster</title>\n");
          client.println("<style>");
          client.println( "html{background-color:#FFCCCC; font-size:7em;text-align:center;}");
          client.println(".title{text-align:center;color:darkblue;font-size:2em;}");
          client.println("a{display:block;text-decoration:none;");
          client.println("width:900px;text-align:center;margin:0 auto;margin-top:200px;font-size:0.7em;}");
          client.println("btn1{background-color:black;color:white;}");
          client.println("</style>");
          client.println("</head>\n");
          client.println("<body>");
          client.println("<h1 class=\"title\">Playing Hamster</h1>");
          client.print("<a class=\"btn1\">打到幾隻地鼠了？</a>");
          client.println(correct);
          client.println("</body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    //
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
    
  }
  delay(1800);
  
  digitalWrite(GreenPin, LOW);digitalWrite(BluePin, LOW); digitalWrite(RedPin, LOW);
  delay(200);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}




