// pin number, where relay is connected
#define RELAY1_PIN 9 //Stufe 3
#define RELAY2_PIN 10 //Stufe 1
#define RELAY3_PIN 11 //Schalter L
#define RELAY4_PIN 12 //Schalter N
// variable to store current relay state
byte stufe1 = 0;
byte stufe2 = 1;
byte stufe3 = 0;
byte powerState = 1;

ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_BINARY(getPowerState, setPowerState),
                    ZUNO_SWITCH_BINARY(getStufe1State, setStufe1State),
                    ZUNO_SWITCH_BINARY(getStufe3State, setStufe3State)
                    //ZUNO_SENSOR_BINARY(General, getStufe2State),
                   );


void setup() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(RELAY4_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  digitalWrite(RELAY3_PIN, HIGH);
  digitalWrite(RELAY4_PIN, HIGH);
}

void loop() {
  // loop is empty, because all the control comes over the Z-Wave
}

byte getStufe1State() {
  return stufe1;
}
/*byte getStufe2State() {
  return stufe2;
  }*/
byte getStufe3State() {
  return stufe3;
}
byte getPowerState() {
  return powerState;
}

void setStufe1State(byte value) {
  if (powerState == 1) {
    digitalWrite(RELAY1_PIN, HIGH);
    digitalWrite(RELAY2_PIN, (value > 0) ? LOW : HIGH);
    stufe2 = (value > 0) ? 0 : 1;
    stufe1 = value;
    stufe3 = 0;
  }
  else {}
  for (int i = 1; i < 5; i++) {
    zunoSendReport(i);
  }
}
void setStufe3State(byte value) {
  if (powerState == 1) {
    digitalWrite(RELAY2_PIN, HIGH);
    digitalWrite(RELAY1_PIN, (value > 0) ? LOW : HIGH);
    stufe2 = (value > 0) ? 0 : 1;
    stufe3 = value;
    stufe1 = 0;
  }
  else {}
  for (int i = 1; i < 5; i++) {
    zunoSendReport(i);
  }
}
void setPowerState(byte value) {
  digitalWrite(RELAY3_PIN, (value > 0) ? HIGH : LOW);
  digitalWrite(RELAY4_PIN, (value > 0) ? HIGH : LOW);
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  stufe1 = 0;
  stufe2 = (value > 0) ? 1 : 0;
  stufe3 = 0;
  powerState = value;
  for (int i = 1; i<  5; i++) {
    zunoSendReport(i);
  }
}
