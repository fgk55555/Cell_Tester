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
float dischargeCurrent  = 1.0;
float currentVoltage[CELLS] = {0.0};
int channel[CELLS] = {A0,A1,A2,A3,A4};
int control[CELLS] = {7,6,5,4,3};
unsigned long startTime = 0;
unsigned long currentTime = 0;
unsigned long lastTime = 0;
unsigned int mAh[CELLS] = {0};
unsigned int pwm[CELLS] ={0};
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
  if(testRunning){
    for(int i=0;i<CELLS;++i){
      currentVoltage[i] = (5/1023)*analogRead(channel[i]);
      //mAh += 
      pwm[i] = (dischargeCurrent / (currentVoltage[i]/resistorOhms)) * 256;
      analogWrite(control[i], pwm[i]);
    }
  }
  delay(100);

  if (Serial.available()) {
    recvCommand();
  }
}
