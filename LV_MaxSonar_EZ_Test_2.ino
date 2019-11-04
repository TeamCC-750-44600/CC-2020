#define TOLERANCE 2
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

void setup() 
{
  pinMode(analogPin, INPUT);
  pinMode(pwPin, INPUT);
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
	Serial.print("Threshold: ")
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
	    PORTB &= B11110111;
		  PORTB |= B00010000;
	  }
	  else if(currVal - TOLERANCE > storedVal)
	  {
	    PORTB &= B11101111;
	    PORTB |= B00001000;
	  }
	  else
	  {
		  PORTB &= B11100111;
	  }
	}
	else
	{
	  PORTB &= B11100111;
	}
}
