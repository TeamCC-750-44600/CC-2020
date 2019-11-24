#define TOLERANCE 1
#define DELAYTIME 100
#define MIN_VALUE 7

class sensor
{
  private:
  int anPin;
  int pwPin;

  //Following readSensor funcions from https://www.maxbotix.com/Arduino-Ultrasonic-Sensors-085/ with constants modified
  public:
  int readSensor()//Read using analog voltage
  {
    double anVolt = analogRead(anPin);
    double inches = anVolt/2; //Takes mm and converts it to inches
    return (int)inches;
  }
  
  void debug()//Will simply print out readings in serial monitor
  {
    
    Serial.println(readSensor());
    
  }
  sensor(int anPinIn, int pwPinIn)//constructor
  {
    anPin = anPinIn;
    pwPin = pwPinIn;
  }
};
const int analogPin = A0;
const int pwPin = 5;
sensor sonarSensor(analogPin, pwPin);
byte prevValue = 0;//2 for moving closer, 1 for moving away

void setup() 
{
  pinMode(analogPin, INPUT);
  pinMode(pwPin, INPUT);
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.print("Threshold: ");
  Serial.print(TOLERANCE/DELAYTIME * 100);
  Serial.print(" inches per second\n");
}

void loop() 
{
  int storedVal = sonarSensor.readSensor();
  delay(DELAYTIME);
  int currVal = sonarSensor.readSensor();
  if(currVal > MIN_VALUE)
  {
    if(currVal + TOLERANCE < storedVal)
    {
      //PORTB &= B11110111;
      digitalWrite(11, LOW);
      if(prevValue == 2)
      {

        //PORTB |= B00010000;
        digitalWrite(12, HIGH);
      }
      else
      {
        prevValue = 2;
      }
    }
    else if(currVal - TOLERANCE > storedVal )
    {
      //PORTB &= B11101111;
      digitalWrite(12, LOW);
      if(prevValue == 1)
      {
        //PORTB |= B00001000;
        digitalWrite(11, HIGH);
      }
      else
      {
        prevValue = 1;
      }
    }
    else
    {
      PORTB &= B11100111;
      //digitalWrite(12, LOW);  
      //digitalWrite(11, LOW);  
      prevValue = 0;
    }
  }
  else
  {
    PORTB &= B11100111;
  }
}




void checkSound()
{
  int counter = 0; 
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
   double frequency = 0;
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
      counter ++;
   }
   //if (speed > alert)
   //{
        peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
       double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
       if (volts > 1.50)
       {
        Serial.println("Squid horn"); 
       }
       Serial.println(volts);
   //}


   
   
   //Serial.print("SignalMax is: ");
   //Serial.println(signalMax);
   //Serial.print("SignalMin is: ");
   //Serial.println(signalMin);
   //Serial.println(counter);
   //frequency = 320/peakToPeak; //To calculate frequency
   //Serial.println(frequency);
}
