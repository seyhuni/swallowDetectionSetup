char dataReady=0;
int muscle = 0;

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1000 Hz (16000000/((249+1)*64))
  OCR1A = 249;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  // initialize the serial communication:
  Serial.begin(4800);
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
    muscle = analogRead(A0);
    //sicaklik = analogRead(A1);
    //tarti = analogRead(A2);
    if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
      Serial.println('!');
    }
    else{
      // send the value of analog input 0:
//        Serial.print("DATA,TIME,");
        Serial.println(muscle);
//        Serial.print(";");
//        Serial.print(sicaklik);
//        Serial.print(";");
//        Serial.print(tarti);
        Serial.println("");
    }
  }
}

ISR(TIMER1_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
  dataReady=1;
}
