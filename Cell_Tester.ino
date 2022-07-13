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

void setup() {
  Serial.begin(115200);
  pinMode(CH_1, INPUT);
  pinMode(CH_2, INPUT);
  pinMode(CH_3, INPUT);
  pinMode(CH_4, INPUT);
  pinMode(CH_5, INPUT);

}

void loop() {
  

}
