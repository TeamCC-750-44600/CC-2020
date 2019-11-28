#define TOLERANCE 1
#define DELAYTIME 100
#define MIN_VALUE 7
#define MIC_PIN A0
#define SONAR_PIN A1
#define SOUND_LED 10
#define SONAR_CLOSER 11
#define SONAR_FURTHER 12

#include <fix_fft.h> // github.com/kosme/fix_fft
#define SEARCH_FREQ 6// 440 hertz, found experimentally
//Increase about 100 hertz per output

char im[128], data[128];
int val;//Counter

class sensor
{
	private:
	int anPin;

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
	sensor(int anPinIn)//constructor
	{
		anPin = anPinIn;
	}
};
sensor sonarSensor(SONAR_PIN);
byte prevValue = 0;//2 for moving closer, 1 for moving away

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
	if(dat > 3)				// If it's above a certain tolerance
		digitalWrite(SOUND_LED, HIGH);
	else
		digitalWrite(SOUND_LED, LOW);
}

void setup() 
{
	Serial.begin(9600);
	pinMode(SONAR_CLOSER, OUTPUT);
	//pinMode(SONAR_FURTHER, OUTPUT);
	pinMode(SOUND_LED, OUTPUT);
	Serial.print("Threshold: ");
	Serial.print(TOLERANCE/DELAYTIME * 100);
	Serial.print(" inches per second\n");
}

void loop() 
{
	int storedVal = sonarSensor.readSensor();
	int startMs = millis();
	while (millis()-startMs < DELAYTIME)
	{
		sound_check();
	}//Wait for DELAYTIME milliseconds
	int currVal = sonarSensor.readSensor();
	if(currVal > MIN_VALUE)
	{
		if(currVal + TOLERANCE < storedVal)
		{
			//PORTB &= B11110111;
			//digitalWrite(SONAR_FURTHER, LOW);
			if(prevValue == 2)
			{
			PORTB |= B00010000;
			digitalWrite(SONAR_CLOSER, HIGH);
			}
			else
			{
				prevValue = 2;
			}
		}
#if 0
		else if(currVal - TOLERANCE > storedVal )
		{
			//PORTB &= B11101111;
			digitalWrite(SONAR_CLOSER, LOW);
			if(prevValue == 1)
			{
				//PORTB |= B00001000;
				digitalWrite(SONAR_FURTHER, HIGH);
			
			else
			{
				prevValue = 1;
			}
		}
#endif
		else
		{
			//PORTB &= B11100111;
			digitalWrite(SONAR_CLOSER, LOW);	
			//digitalWrite(SONAR_FURTHER, LOW);	
			prevValue = 0;
		}
	}
}
