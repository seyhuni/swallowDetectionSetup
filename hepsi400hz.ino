//#include "HX711.h"  //You must have this library in your arduino library folder
//#include <Q2HX711.h>


#define DOUT  3
#define PD_SCK  2
#define GAIN 1
#define SCALE  -846640.0
//HX711 scale(DOUT, CLK);
//Q2HX711 hx711(DOUT, CLK);

//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -846640; //-106600 worked for my 40Kg max scale setup 
float agirlik;
float new_agirlik;
char dataReady=0;
int emgpin = A0;
int ekg = 0;
int emgReading; 
int ThermistorPin = A1;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

long OFFSET=0;

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 830.0477277443453 Hz (12000000/((14456+1)*1))
//  OCR1A = 14456;
  OCR1A = 624;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();

//    OCR1A = 1249;   //200
//  // CTC
//  TCCR1B |= (1 << WGM12);
//  // Prescaler 64
//  TCCR1B |= (1 << CS11) | (1 << CS10);
//  // Output Compare Match A Interrupt Enable
//  TIMSK1 |= (1 << OCIE1A);
//  interrupts();
//    OCR1A = 13332;
//  // CTC
//  TCCR1B |= (1 << WGM12);
//  // Prescaler 8
//  TCCR1B |= (1 << CS11);
//  // Output Compare Match A Interrupt Enable
//  TIMSK1 |= (1 << OCIE1A);
//  interrupts();

}

long  hx711_read(void)
{
unsigned long value = 0;
uint8_t data[3] = { 0 };
uint8_t filler = 0x00;
  while (!digitalRead(DOUT) == LOW) {
    delay(0);
  }
  
  noInterrupts();
  data[2] = shiftIn(DOUT, PD_SCK, MSBFIRST);
  data[1] = shiftIn(DOUT, PD_SCK, MSBFIRST);
  data[0] = shiftIn(DOUT, PD_SCK, MSBFIRST);
  
  for (unsigned int i = 0; i < GAIN; i++) {
    digitalWrite(PD_SCK, HIGH);
    digitalWrite(PD_SCK, LOW);
  }
  interrupts();
  if (data[2] & 0x80) {
    filler = 0xFF;
  } else {
    filler = 0x00;
  }

  // Construct a 32-bit signed integer
  value = ( static_cast<unsigned long>(filler) << 24
      | static_cast<unsigned long>(data[2]) << 16
      | static_cast<unsigned long>(data[1]) << 8
      | static_cast<unsigned long>(data[0]) );
  return static_cast<long>(value);
}

void setup() {
  // initialize the serial communication:
  Serial.begin(115200);
  //hx711.setGain(128);
//  scale.begin(DOUT, CLK);
//  scale.set_scale();  //Calibration Factor obtained from first sketch
//  scale.tare();             //Reset the scale to 0  
//  Serial.println("CLEARDATA");
//  Serial.println("LABEL,t,A0");

  pinMode(PD_SCK, OUTPUT);
  pinMode(DOUT, INPUT);
  digitalWrite(PD_SCK, LOW);
  OFFSET=hx711_read();
  
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
  setupTimer1();
  OFFSET=hx711_read();
//  scale.set_scale(calibration_factor);

}

void loop() {
    //new_agirlik = scale.get_units();
    //new_agirlik = hx711.read();
    new_agirlik= (float)(hx711_read()-OFFSET)/SCALE;
//    if(new_agirlik>0)
//    {
//        agirlik=new_agirlik;
//     }

    
}

ISR(TIMER1_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
//  dataReady=1;
//  if(dataReady>0)
//  {
//    dataReady=0;
    //sicaklik = analogRead(A1);
    //tarti = analogRead(A2);
    if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
      Serial.println(0);
    }
    else{
        ekg = analogRead(A2);
        emgReading  = analogRead(emgpin);
        Vo = analogRead(ThermistorPin);
        R2 = R1 * (1023.0 / (float)Vo - 1.0);
        logR2 = log(R2);
        T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
        Tc = T - 273.15;

        Serial.print(emgReading);
        Serial.print(";");
        Serial.print(Tc);
        Serial.print(";");
        Serial.print(ekg);
        Serial.print(";  ");
        Serial.println(new_agirlik,3);  //Up to 3 decimal points
    }
}
