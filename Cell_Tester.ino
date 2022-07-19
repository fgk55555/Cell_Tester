#define CELLS 5
#define LIFEPO4_MIN 3.62
#define LIFEPO4_MAX 3.66
#define LIPO_MIN  4.1
#define LIPO_MAX  4.22
#define LIPO 2
#define LIFEPO4 1
#define UNDEFINED 0

float dischargeVoltage = 2.5;
float resistorOhms = 1.0;
float currentVoltage[CELLS] = {0.0};
float mAh[CELLS] = {0};
int channel[CELLS] = {A0,A1,A2,A3,A4};
int control[CELLS] = {7,6,5,4,3};
unsigned long startTime = 0;
unsigned long currentTime = 0;
unsigned long lastTime = 0;
unsigned int pwm[CELLS] ={0};
unsigned int dischargeCurrent  = 1000; //In milliamps
byte cellType[CELLS] = {0};
bool testRunning = false;

void setup() {
  Serial.begin(115200);
  for(int i=0;i<CELLS;++i){
    pinMode(channel[i], INPUT);
    pinMode(control[i], OUTPUT);
    digitalWrite(control[i], 0); //Set all control channels low
  }
  checkCells();
  Serial.println("Waiting for test start");
  Serial.println("Commands:");
  Serial.println("S - start/ stop test");
  Serial.println("A:X.XX - set discharge current");
  Serial.println("V:X.XX - set dischage voltage");
}

void loop() {
  byte count = 0;
  if(testRunning){
    currentTime = millis();
    for(int i=0;i<CELLS;++i){
      if(cellType[i] != UNDEFINED){
        currentVoltage[i] = (5/1023)*analogRead(channel[i]);
        mAh[i] += (dischargeCurrent * (currentTime - lastTime)) / 3600; //Millisecond to hour conversion
        pwm[i] = ((dischargeCurrent/1000) / (currentVoltage[i]/resistorOhms)) * 256;
        analogWrite(control[i], pwm[i]);
      }
    }
    lastTime = millis();
    if(count >= 50){
      count = 0;
      printValues();
    }
    else
      ++count;
  }
  delay(100);
  ++count;

  if (Serial.available()) {
    recvCommand();
  }
}
