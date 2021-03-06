char dataReady=0;
int ThermistorPin = 1;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 830.0477277443453 Hz (12000000/((14456+1)*1))
  OCR1A = 14456;
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
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
  setupTimer1();

}

void loop() {
  if(dataReady>0)
  {
    dataReady=0;
    Vo = analogRead(ThermistorPin);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    Tc = T - 273.15;

      // send the value of analog input 0:
//        Serial.print("DATA,TIME,");
        Serial.println(Tc);
//        Serial.print(";");
//        Serial.print(sicaklik);
//        Serial.print(";");
//        Serial.print(tarti);
//        Serial.println("");
    }
  }


ISR(TIMER1_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
  dataReady=1;
}
