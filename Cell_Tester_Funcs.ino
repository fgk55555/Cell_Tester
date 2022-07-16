void checkCells(){
  for(int i=0;i<CELLS;++i){
    currentVoltage[i] = (5/1023)*analogRead(channel[i]);  //Check voltages on each cell
    if(currentVoltage[i] >= LIFEPO4_MIN && currentVoltage[i] <= LIFEPO4_MAX){
      cellType[i] = LIFEPO4;
    }
    else if(currentVoltage[i] >= LIPO_MIN && currentVoltage[i] <= LIPO_MAX){
      cellType[i] = LIPO;
    }
    Serial.print("Starting voltages, slot ");Serial.print(i);
    Serial.print(": ");Serial.print(currentVoltage[i]);
    Serial.print("\t Cell is: ");
    if(cellType == LIPO){
      Serial.println("charged lipo");
    }
    else if(cellType == LIFEPO4){
      Serial.println("charged LIFEPO4");
    }
    else{
      Serial.println("unknown");
    }
  }
}

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
      startTime = millis();
    }
  }
  else if(inputString.startsWith("C")){ //Set the discharge current
    dischargeCurrent = atof(pieces[1]);
    Serial.print("Discharge current set to: ");Serial.println(dischargeCurrent);
  }
  else if(inputString.startsWith("V")){ //Change minimum voltage
    dischargeVoltage = atof(pieces[1]);
    Serial.print("Discharge voltage set to: ");Serial.println(dischargeVoltage);
  }
  else{
    Serial.println("Command not recognized");
  }
}
