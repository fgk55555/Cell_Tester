void recvCommand(){
  String inputString = "";
  while(Serial.available()){
    char inChar = (char)Serial.read();
    if (inChar >= 'A' && inChar <= 'Z' || inChar >= '0' && inChar <= ':' 
    || inChar == '\n' || inChar == '-' || inChar == '.'){ 
      inputString += inChar;
      if (inChar == '\n'){
        Serial.flush();
        CommandProcess(inputString);
      } 
    }    
  }
}

void CommandProcess(String inputString){
  int i=0;
  int len = inputString.length();
  char inputChars[50];
  for(i=0;i<=len;++i){
    inputChars[i]=inputString[i];
  }
  char* command = strtok(inputChars, ": "); //break up input string
  char pieces[2][10];
  i = 0;
  
  while(command != NULL){ //iterate through sections
    if(i < 5){
      strcpy(pieces[i++], command);
      command = strtok(NULL, ":"); //This moves to next chunk
    }
  }
  if(inputString.startsWith("S")){ //Stream position
    if(testRunning){
      testRunning = false;
      Serial.println("Stopping test");
    }
    if(testRunning){
      testRunning = true;
      Serial.println("Starting test");
    }
  }
  else if(inputString.startsWith("C")){ //Set the discharge pwm
    dischargeCurrent = atoi(pieces[1]);
    Serial.print("Discharge current pwm set to: ");Serial.println(dischargeCurrent);
  }
  else if(inputString.startsWith("V")){ //Change minimum voltage
    dischargeVoltage = atof(pieces[1]);
    Serial.print("Discharge voltage set to: ");Serial.println(dischargeVoltage);
  }
  else{
    Serial.println("Command not recognized");
  }
}
