/*
   YF-S201 Hall Effect Water Flow Meter / Sensor
   http://www.hobbytronics.co.uk/yf-s201-water-flow-meter

   Read Water Flow Meter and output reading in litres/hour

*/

volatile int  flow_frequency;  // Measures flow meter pulses
unsigned int  l_min;          // Calculated litres/min
unsigned char flowmeter = 2;  // Flow Meter Pin number
unsigned long currentTime;
unsigned long cloopTime;

void flow ()                  // Interruot functionlitres/min
{
   flow_frequency++;
}

void setup()
{
   pinMode(flowmeter, INPUT);
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING); // Setup Interrupt
                                     // see http://arduino.cc/en/Reference/attachInterrupt
   sei();                            // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
}

void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime;              // Updates cloopTime
      // Pulse frequency (Hz) = 6.6Q, Q is flow rate in L/min. (Results in +/- 3% range)
      l_hour = (flow_frequency / 6.6); // (Pulse frequency / 6.6Q = flow rate in litres/min
      flow_frequency = 0;                   // Reset Counter

      Serial.print(l_min, DEC);            // Print litres/min
      Serial.print(" l_min       ");

      Serial.print(l_min*60, DEC);            // Print litres/hour
      Serial.println(" L/hour");
   }
}
