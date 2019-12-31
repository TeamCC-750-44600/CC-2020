const int MIN_LIGHT = 8;
const int MAX_LIGHT = 256;
const int SUN = 10;
const int BUTTON = 2;
const int PUMP = 9;
const int VACUUM = 11; 

bool but_press = false;
int state = 0;

void setup()
{
  pinMode (SUN, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(VACUUM, OUTPUT);
  pinMode(BUTTON, INPUT);
  analogWrite(SUN, MAX_LIGHT);
}
#define E 2.7182818284590452353602874713527

void loop()
{
  state = digitalRead(BUTTON);
  if(state == LOW)
  {
    if(but_press == false)
    {
        for (int ii = MAX_LIGHT; ii >= MIN_LIGHT; ii-=4)
        {
          analogWrite(SUN, ii);
          delay(50);
        }
        digitalWrite(VACUUM, LOW);
        digitalWrite(PUMP, HIGH);
    }
    else
    {
      for (int ii = MIN_LIGHT; ii <= MAX_LIGHT; ii+=4)
      {
        analogWrite(SUN, ii);
        delay(50);
      }
        digitalWrite(PUMP, LOW);
        digitalWrite(VACUUM, HIGH);
    }
    but_press = !but_press;
  }
}
