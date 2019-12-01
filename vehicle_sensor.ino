#define TOLERANCE 1
#define DELAYTIME 100
#define MIN_VALUE 7
#define MIC_PIN A0
#define SONAR_PIN A1
#define SOUND_LED 10
#define SONAR_CLOSER 11
#define SONAR_FURTHER 12
#define TIME_THRESHOLD 1

#define MIN_VOLUME 3

#include <fix_fft.h> // github.com/kosme/fix_fft
#define SEARCH_FREQ 6// About 370-470 hertz, found experimentally

char im[128], data[128];
int val;//Counter

unsigned long consTimes = 0;//Number of consecutive sensor readings in which something is moving closer
class sensor
{
	private:
	int anPin;

	//Following readSensor funcions from https://www.maxbotix.com/Arduino-Ultrasonic-Sensors-085/ with constants modified
	public:
	double readSensor()//Read using analog voltage
	{
		double anVolt = analogRead(anPin);
		double inches = anVolt/2; //Takes input and converts it to inches
		Serial.println(inches);
		return inches;
	}
	
	void debug()//Will simply print out readings in serial monitor
	{
		
		Serial.println(readSensor());
		
	}
	sensor(int anPinIn)//constructor
	{
		anPin = anPinIn;
	}
};
sensor sonarSensor(SONAR_PIN);

void sound_check()
{
	//int min = 1024, max = 0;
	for(int ii = 0; ii < 128; ii++)		// Take 128 samples
	{
		val = analogRead(MIC_PIN);	// Read in value
		data[ii] = val/4 - 120;		// Populate array
		im[ii] = 0;			//
	}
	fix_fft(data, im, 7, 0);		// Dark magic happens here
	int dat = sqrt(data[SEARCH_FREQ]*data[SEARCH_FREQ] + im[SEARCH_FREQ] * im[SEARCH_FREQ]); //Clean up values? Not really sure, but this seems important
	if(dat > MIN_VOLUME)			// If it's above a certain tolerance
	{
		digitalWrite(SOUND_LED, HIGH);
	}
	else
	{
		digitalWrite(SOUND_LED, LOW);
	}
	//Serial.println(dat);
}

void setup() 
{
	Serial.begin(9600);
	pinMode(SONAR_CLOSER, OUTPUT);
	//pinMode(SONAR_FURTHER, OUTPUT);
	pinMode(SOUND_LED, OUTPUT);
//	Serial.print("Threshold: ");
//	Serial.print(TOLERANCE/DELAYTIME * 100);
//	Serial.print(" inches per second\n");
}

void loop() 
{
	double storedVal = sonarSensor.readSensor();
	unsigned long startMs = millis();
	while (millis()-startMs < DELAYTIME)
	{
		sound_check();
	}//Repeat for DELAYTIME milliseconds
	double currVal = sonarSensor.readSensor();
	if(currVal > MIN_VALUE)
	{
		if(currVal + TOLERANCE < storedVal)
		{
			if(consTimes >= TIME_THRESHOLD)
			{
				digitalWrite(SONAR_CLOSER, HIGH);
			}
			else
			{
				consTimes++;
			}
		}
		else
		{
			digitalWrite(SONAR_CLOSER, LOW);	
			consTimes = 0;
		}
	}
}
