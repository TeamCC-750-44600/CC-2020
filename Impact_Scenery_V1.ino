
int MIN_LIGHT = 8;
int MAX_LIGHT = 256;
int sun = 10;
int state = 0;
int button = 2;
int pump = 9;
int vacuum = 11; 

void setup()
{
  pinMode (sun, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(vacuum, OUTPUT);
  pinMode(button, INPUT);
  for (int ii = 0; ii <= MIN_LIGHT; ii++)
  {
    analogWrite(sun, ii);
    delay(50);
  }
}


void loop()
{
  digitalWrite
  digitalWrite(pump, HIGH);
  state = digitalRead(button);
  if(state == LOW)
  {
    for (int ii = MIN_LIGHT; ii < MAX_LIGHT; ii++)
    {
      analogWrite(sun, ii);
      delay(10);
    }
    digitalWrite(pump, LOW);
    digitalWrite(vacuum, HIGH);
  }
}
