char dataReady=0;
int emgpin = A0;     // the FSR and 10K pulldown are connected to a0
int emgReading;     // the analog reading from the FSR resistor divider
void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 810.0477277443453 Hz (12000000/((14456+1)*1))
  OCR1A = 14813;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 1
  TCCR1B |= (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  // initialize the serial communication:
  Serial.begin(115200);
//  Serial.println("CLEARDATA");
//  Serial.println("LABEL,t,A0");
  setupTimer1();

}

void loop() {
  if(dataReady>0)
  {
    dataReady=0;
    emgReading  = analogRead(emgpin);
   

      // send the value of analog input 0:
//        Serial.print("DATA,TIME,");
        Serial.println(emgReading);

    }
  }


ISR(TIMER1_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
  dataReady=1;
}

