#include <ESP8266WiFi.h>
const char* WIFI_SSID = "<Your own SSID>";
const char* WIFI_PASSWORD = "";
const IPAddress WIFI_IP(192,168,10,19);
const IPAddress WIFI_MASK(255,255,255,0);
const IPAddress WIFI_GATEWAY(192,168,10,254);
const int WIFI_SERVER_PORT = 8090;
WiFiServer mWifi_server(WIFI_SERVER_PORT);
WiFiClient mWifi_client;
bool is_client_connected = false;
//**************************WiFi-Connection*****************************
void wifi_connect(){
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);  
    /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
       would try to act as both a client and an access-point and could cause
       network-issues with your other WiFi-devices on your WiFi-network. */
    WiFi.mode(WIFI_STA);
    WiFi.config(WIFI_IP,WIFI_GATEWAY,WIFI_MASK);
    WiFi.begin(WIFI_SSID);    
    while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
  }
}

void wifi_server_init(){  
  mWifi_server.close();
  mWifi_server.begin();
  Serial.print("Server is started, port=[");
  Serial.print(WIFI_SERVER_PORT);
  Serial.println("]");
}

void check_wifi_clinet_connection(){ 
  if(!mWifi_client){
    is_client_connected = false;
    mWifi_client = mWifi_server.available();
    delay(10);
  }    
  if(mWifi_client){
    if(mWifi_client.connected()){
      if(!is_client_connected){
        Serial.println("Client connected");
        Serial.print("Client IP: ");
        Serial.println(mWifi_client.remoteIP());
        is_client_connected = true;
      }
    }
    else{
      if(is_client_connected){
        Serial.println("Client is disconnected");
      }
      is_client_connected = false;
      mWifi_client.stop();
    }    
  }
}

String read_from_client(){
    String receiving_msg = "";
    receiving_msg = mWifi_client.readStringUntil('\n');
    receiving_msg.trim();
    mWifi_client.flush();
    return receiving_msg;
}

void reply_to_client(String id,String cmd, String result,String more = ""){
  if(mWifi_client){
    String reply_msg = String(id+COMMAND_SPLITTER+cmd+COMMAND_SPLITTER+result);
    if(more != "") reply_msg = String(reply_msg + COMMAND_SPLITTER + more);
    mWifi_client.println(reply_msg);
  }
}
