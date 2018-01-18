void loop() {
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("WiFi disconnected, try to reconnect...");
    wifi_connect();
  }
  check_wifi_clinet_connection();
  if(mWifi_client.available()){
    String raw_data = read_from_client();
    Serial.print("Data received:");
    Serial.println(raw_data);
    command_parser(raw_data); //<--Parser Module
    elapseExample();
  }
}
