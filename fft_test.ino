#define MIC_PIN A0
#include <fix_fft.h> // github.com/kosme/fix_fft

char im[128], data[128];
int val;//Counter
void setup()
{
	Serial.begin(9600);
	analogReference(DEFAULT);
}

void loop()
{
	//int min = 1024, max = 0;
	for(int ii = 0; ii < 128; ii++)		//Take 128 samples
	{
		val = analogRead(MIC_PIN);	//Read in value
		data[ii] = val/4 - 120;		//Populate array
		im[ii] = 0;			//???
	}
	fix_fft(data, im, 7, 0);		//Dark magic happens here
	for(char ii = 1; ii < 64; ii++)		//Print out all values
	{
		int dat = sqrt(data[ii]*data[ii] + im[ii] * im[ii]);//Clean up values? Not really sure; but this seems important
		Serial.print(dat);
		Serial.print(" ");
	}					//Note: Printing all values such that you can compare a value with the one above it
	Serial.print("\n");
}

