int buttonValue = 0;
bool constLight = false;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
int state = 0;
int delayToWait = 0; // ms

const int LED1_OUT = 8; // Pin 8
const int LED2_OUT = 9; // Pin 9
const int BUTTON_IN = 10; // Pin 10

const int BlinkLenghtFrom = 1000; // ms
const int BlinkLenghtTo = 2000; // ms
const int BlinkSpacingFrom = 2000; // ms
const int BlinkSpacingTo = 3000; // ms

void setup() {
  pinMode(LED1_OUT, OUTPUT);
  pinMode(LED2_OUT, OUTPUT);
  pinMode(BUTTON_IN, INPUT);
  randomSeed(analogRead(0));
}

void loop()
{
  currentMillis = millis();
  buttonValue = digitalRead(BUTTON_IN);
  if (buttonValue > 0)
  {
    constLight = !constLight;
    LightLED();
    RestartState();
    delay(500);
    return;
  }

  if (constLight)
  {
    LightLED();
    RestartState();
  }
  else
  {
    HandleState();
  }
}

void HandleState()
{
  if (state == 0)
  {
    digitalWrite(LED1_OUT, HIGH);
    SetDelay(35);
    state++;
  }
  if (state == 1)
  {
    if (DidTimePass())
    {
      state++;
    }
  }
  if (state == 2)
  {
    digitalWrite(LED2_OUT, HIGH);
    SetDelay(random(BlinkLenghtFrom, BlinkLenghtTo));
    state++;
  }
  if (state == 3)
  {
    if (DidTimePass())
    {
      state++;
    }
  }
  if (state == 4)
  {
    PutOffLED();
    SetDelay(random(BlinkSpacingFrom, BlinkSpacingTo));
    state++;
  }
  if (state == 5)
  {
    if (DidTimePass())
    {
      RestartState();
    }
  }
}

void RestartState()
{
  state = 0;
}

bool DidTimePass()
{
  bool passed = currentMillis - previousMillis >= delayToWait;
  if(passed)
  {
    previousMillis = currentMillis;
  }
  return passed;
}

void SetDelay(int delay){
  delayToWait = delay;
  previousMillis = millis();
}

void LightLED() {
  digitalWrite(LED1_OUT, HIGH);
  digitalWrite(LED2_OUT, HIGH);
}

void PutOffLED() {
  digitalWrite(LED1_OUT, LOW);
  digitalWrite(LED2_OUT, LOW);
}
