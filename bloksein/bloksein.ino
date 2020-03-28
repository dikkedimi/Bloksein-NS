#define RedPin 9
#define YellowPin 10
#define GreenPin 11
#define SupplyPin 12
#define Block1Input 8
#define Block2Input 7
#define Block3Input 6
enum state { 
  STOP, 
  EXPECTSTOP, 
  SAFE, 
  CLOSEDTRACK,
  ONSIGHTMAX40, 
  MAX40
  }; // OFF = 0 and NBSTATE=7

int SupplyState=HIGH;
char state;
int DelayTime = 1000;
int Block1Reading;
int Block2Reading;
int Block3Reading;
unsigned long currentMillisBlink;
unsigned long previousMillisBlink;
unsigned long BlinkInterval;
// Read parameters
unsigned long currentMillisRead;
unsigned long previousMillisRead;
unsigned long ReadInterval = 1000;

const long BasePeriod = 350;
const long FAST = BasePeriod/2;           // interval at which to blink (milliseconds)
const long REGULAR = BasePeriod;
const long SLOW = BasePeriod*4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  Serial.print("RedPin = ");
//  Serial.println(RedPin);
  pinMode(Block1Input,INPUT);
  pinMode(Block2Input,INPUT);
  pinMode(Block3Input,INPUT);
  pinMode(RedPin, OUTPUT);
//  Serial.print("YellowPin = ");
//  Serial.println(YellowPin);
  pinMode(YellowPin, OUTPUT);
//  Serial.print("GreenPin = ");
//  Serial.println(GreenPin);
  pinMode(GreenPin, OUTPUT);
  pinMode(SupplyPin, OUTPUT);
  digitalWrite(RedPin,HIGH);
  digitalWrite(YellowPin,HIGH);
  digitalWrite(GreenPin,HIGH);
  digitalWrite(SupplyPin,HIGH);
//  void Switch(int state);

}

void loop() {
//  Serial.println("Main Loop");
//  currentMillis = millis();
//  unsigned long interval = 1000;
//  if (currentMillis - previousMillis >= interval) {
//    // save the last time you blinked the LED
//    previousMillis = currentMillis;
//    
//    Serial.println("BLOCK LOGIC");
    if(Block1Reading == 1 ) {
//      Serial.println("STOP");
      state = STOP; //STOP
      Switch(state);
    }  
    if(Block2Reading == 1) {
//      Serial.println("ONSIGHTMAX40");
      state = ONSIGHTMAX40; //ONSIGHTMAX40
      Switch(state);
    } 
    if(Block3Reading == 1) {
//      Serial.println("EXPECTSTOP");
      state = EXPECTSTOP; //SAFE 
      Switch(state);
    } else if(!Block1Reading && !Block2Reading && !Block3Reading) {
//      Serial.println("SAFE");
      state = SAFE;
      Switch(state);
    }
  readBlocks();   
//  }

}

void Switch(int state) {
  
//  Serial.println("Switch");
  switch (state) {
    default: STOP:
    digitalWrite(RedPin,LOW);
    digitalWrite(YellowPin,HIGH);
    digitalWrite(GreenPin,HIGH);
//    Serial.print("State = ");
//    Serial.println(state);
    break;
    case CLOSEDTRACK:
    digitalWrite(RedPin,LOW);
    digitalWrite(YellowPin,HIGH);
    digitalWrite(GreenPin,HIGH);
    BlinkLedAsym();
//    Serial.print("State = ");
//    Serial.println(state);
    break;
    case ONSIGHTMAX40:
    digitalWrite(RedPin,HIGH);
    digitalWrite(YellowPin,LOW);
    digitalWrite(GreenPin,HIGH);
    BlinkLed();
//    Serial.print("State = ");
//    Serial.println(state);
    break;
    case EXPECTSTOP:
    digitalWrite(SupplyPin, HIGH);
    digitalWrite(RedPin,HIGH);
    digitalWrite(YellowPin,LOW);
    digitalWrite(GreenPin,HIGH);
//    Serial.print("State = ");
//    Serial.println(state);
    break;
    case MAX40:
    digitalWrite(RedPin,HIGH);
    digitalWrite(YellowPin,HIGH);
    digitalWrite(GreenPin,LOW);
        BlinkLed();
//    Serial.print("State = ");
//    Serial.println(state);
    break;
    case SAFE:
    digitalWrite(SupplyPin, HIGH);
    digitalWrite(RedPin,HIGH);
    digitalWrite(YellowPin,HIGH);
    digitalWrite(GreenPin,LOW);
//    Serial.print("State = ");
//    Serial.println(state);
    break;
  break;

  }
}

void BlinkLed() {
  currentMillisBlink = millis();
  if (currentMillisBlink - previousMillisBlink >= BlinkInterval) {
     Serial.println("BlinkLed");
     BlinkInterval= REGULAR;
    // save the last time you blinked the LED
    previousMillisBlink = currentMillisBlink;
    // if the LED is off turn it on and vice-versa:
    if (SupplyState == LOW) {
      SupplyState = HIGH;
    } else {
      SupplyState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(SupplyPin, SupplyState);
//    return;
  }
  
}

void BlinkLedAsym() {
  unsigned long currentMillisBlink = millis();
  //  Serial.print(", Supplystate: ");
//  Serial.println(SupplyState);
  if (currentMillisBlink - previousMillisBlink >= BlinkInterval) {
    Serial.println("Blink Asymmetrycally");
    // save the last time you blinked the LED
    previousMillisBlink = currentMillisBlink;
    SupplyState = !SupplyState;
    // if the LED is off turn it on and vice-versa:
    if (SupplyState == LOW)
    {
      BlinkInterval = FAST;
//      Serial.print("interval FAST: ");
//      Serial.println(BlinkInterval );
      digitalWrite(SupplyPin, HIGH);
      }
    else
    {
      BlinkInterval= SLOW;
//      Serial.print("interval SLOW: ");
//      Serial.println(BlinkInterval );
      digitalWrite(SupplyPin, LOW);
      }
  }
//return;
}
void readBlocks() {
  
  currentMillisRead = millis();
  unsigned long ReadInterval = 1000;
  if (currentMillisRead - previousMillisRead >= ReadInterval) {
    Serial.println("Reading Blocks");
    // save the last time you blinked the LED
    previousMillisRead = currentMillisRead;
    Block1Reading= digitalRead(Block1Input);
//  Serial.print("Block1Reading: ");
//  Serial.println(Block1Reading);
    Block2Reading= digitalRead(Block2Input);
//  Serial.print("Block2Reading: ");
//  Serial.println(Block2Reading);
    Block3Reading= digitalRead(Block3Input);
//  Serial.print("Block3Reading: ");
//  Serial.println(Block3Reading);
//    return;
  } else {
    return;
  }
}
