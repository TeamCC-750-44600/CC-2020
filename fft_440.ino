#define MIC_PIN A0
#include <fix_fft.h>
#define SEARCH_FREQ 6//440 hertz, found experimentally
//Increase about 100 hertz per output

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
	for(int ii = 0; ii < 128; ii++)//Take 128 samples
	{
		val = analogRead(MIC_PIN);
		data[ii] = val/4 - 120;//Populate array
		im[ii] = 0;
	}
	fix_fft(data, im, 7, 0);//Dark magic happens here
	int dat = sqrt(data[SEARCH_FREQ]*data[SEARCH_FREQ] + im[SEARCH_FREQ] * im[SEARCH_FREQ]);
	if(dat > 3)
		Serial.print("Sound detected\t");
}

