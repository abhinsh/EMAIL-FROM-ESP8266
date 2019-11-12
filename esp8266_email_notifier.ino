#include <ESP8266WiFi.h>  // the ESP8266WiFi.h  lib
#include <WiFiClient.h>
char server[] = "YOUR EMAIL SERVER eg. mail.XXXXXXX####XXXX.com";
ADC_MODE(ADC_VCC);
//char* subject1 = "helllo guys"; 
// similarly  i should add more variables with different subjects as per requirement of email notification


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


WiFiClient client;

//**********************************************************************************************************


void connect_wifi() {
  const char* ssid= "SSID of ";
  const char* password = "your password?";
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print(" ");

  WiFi.mode(WIFI_STA); // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.begin(ssid,password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println();
}


//***********************************************************************************************************


//###############################################################################

byte sendEmail(char* ABCD)
{
  byte thisByte = 0;
  byte respCode;

  if (client.connect(server,587) == 1) {
    Serial.println(F("connected"));
  } else {
    Serial.println(F("connection failed"));
    return 0;
  }
  if (!eRcv()) return 0;

  Serial.println(F("Sending EHLO"));
  client.println("EHLO your mail server");
  if (!eRcv()) return 0;
  Serial.println(F("Sending auth login"));
  client.println("auth login");
  if (!eRcv()) return 0;
  Serial.println(F("Sending User"));
  // Change to your base64, ASCII encoded user
  client.println("YWJoaXNoZWtAYXV0b3RlY2hwbC5jb20="); // SMTP UserID
  if (!eRcv()) return 0;
  Serial.println(F("Sending Password"));
  // change to your base64, ASCII encoded password
  client.println("UHdkLzEyMzQ=");//  SMTP Passw
     if (!eRcv()) return 0;
    Serial.println(F("Sending From"));   // change to your email address (sender)
   client.println(F("MAIL From:abhishek@autotechpl.com"));// not important 
   if (!eRcv()) return 0;   // change to recipient address
    Serial.println(F("Sending To"));
    client.println(F("RCPT To:abhishekpoudel1992@gmail.com"));
    if (!eRcv()) return 0;
    Serial.println(F("Sending DATA"));
    client.println(F("DATA"));
    if (!eRcv()) return 0;
    Serial.println(F("Sending email"));   // change to recipient address
   client.println(F("To:abhishekpoudel1992@gmail.com"));   // change to your address
   client.println(F("From:abhishek@autotechpl.com"));
 client.println((String)"Subject:"+ABCD); ///Serial.println((String)"x:"+x+" y:"+y);
    client.print(F("Power is: "));
    client.print(ESP.getVcc());
    client.println(F("mV"));
    client.print(F("Device Chip ID: "));
    client.println(ESP.getChipId());
    Serial.print(F("Voltage is: "));
    Serial.print(ESP.getVcc());
    client.println(F("."));
    if (!eRcv()) return 0;
    Serial.println(F("Sending QUIT"));
    client.println(F("QUIT"));
    if (!eRcv()) return 0;
    client.stop();
    Serial.println(F("disconnected"));
    return 1;
  }
  byte eRcv()
  {
    byte respCode;
    byte thisByte;
    int loopCount = 0;
    while (!client.available())
  {
      delay(1);
      loopCount++;     // if nothing received for 10 seconds, timeout
      if (loopCount > 10000) {
      client.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  respCode = client.peek();
  while (client.available())
  {
    thisByte = client.read();
    Serial.write(thisByte);
  }

  if (respCode >= '4')
  {
    //  efail();
    return 0;
  }
  return 1;
}
//##############################################################################

void setup()
{
  
  Serial.begin(115200);
  delay(100);
  connect_wifi(); 
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  int ledpin1=5;
  int ledpin2=7;
  char* subject2="LEDPIN 2 IS HIGH";
  pinMode(ledpin1, INPUT);
  pinMode(ledpin2, OUTPUT);
  digitalWrite(ledpin2,0);
  int ledpin2_status;
  ledpin2_status=digitalRead(ledpin2);
  if (ledpin2_status==0) delay(500); {
    sendEmail(subject2);
    delay(20000);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

