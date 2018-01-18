
//**************************Command format*****************************
String get_spilted_substring(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++){
    if (data.charAt(i) == separator || i == maxIndex){
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void raw_data_parser(String data,String &id, String &cmd, String parameters[RCV_PARAMETER_MAX]){  
  id = get_spilted_substring(data,COMMAND_SPLITTER,0);
  cmd = get_spilted_substring(data,COMMAND_SPLITTER,1);
  cmd.toLowerCase();
  String para_str = get_spilted_substring(data,COMMAND_SPLITTER,2);
  param_parser(para_str, parameters);
  Serial.print("ID=");
  Serial.println(id);
  Serial.print("Command=");
  Serial.println(cmd);
  for(int i =0 ;i < RCV_PARAMETER_MAX;i++){
    if(parameters[i].length()>0){
      Serial.print("Param[");
      Serial.print(i);
      Serial.print("]=");
      Serial.println(parameters[i]);
    }
  }
}

void param_parser(String para_str,String params[RCV_PARAMETER_MAX]){
  for(int i =0 ;i < RCV_PARAMETER_MAX;i++){
    params[i] = get_spilted_substring(para_str,PARAMETER_SPLITTER,i);
  }
}

void command_parser(String raw_data){
  String rcv_id = "";
  String rcv_command = "";
  String rcv_parameters[RCV_PARAMETER_MAX] ={""};
  
  raw_data_parser(raw_data,rcv_id,rcv_command,rcv_parameters);
  //do your own command here
  //flip_command(rcv_id,rcv_command,rcv_parameters);
}

