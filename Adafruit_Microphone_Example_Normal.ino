/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/
 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
void setup() 
{
   Serial.begin(115200);
}
 
 
void loop() 
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
