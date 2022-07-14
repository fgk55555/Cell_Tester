#define RESISTOR 1.0
#define CH_1 A0
#define CH_2 A1
#define CH_3 A2
#define CH_4 A3
#define CH_5 A4
#define SW1 7
#define SW2 6
#define SW3 5
#define SW4 4
#define SW5 3
#define CELLS 5

float dischargeVoltage = 2.5;
float resistorOhms = 1.0;
float startingVoltages[CELLS] = {0.0};
float currentVoltages[CELLS] = {0.0};
unsigned int mAh[CELLS] = 0;
int dischargeCurrent  = 128;
bool testRunning = false;

void setup() {
  Serial.begin(115200);
  pinMode(CH_1, INPUT);
  pinMode(CH_2, INPUT);
  pinMode(CH_3, INPUT);
  pinMode(CH_4, INPUT);
  pinMode(CH_5, INPUT);
  for(int i=0;i<CELLS;++i){
    startingVoltage[i] = analogRead
  }
  pinMode(SW1, OUTPUT);
  pinMode(SW2, OUTPUT);
  pinMode(SW3, OUTPUT);
  pinMode(SW4, OUTPUT);
  pinMode(SW5, OUTPUT);

  //Check voltages on each 
  
}

void loop() {



  if (Serial.available()) {
    recvCommand();
  }
}
