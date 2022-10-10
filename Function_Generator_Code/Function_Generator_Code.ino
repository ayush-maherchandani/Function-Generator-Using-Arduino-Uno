// Library and Pins for the Display 16x2
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Definitios of global variables
int sine[255];
const int POT = A0;
int value = 0;
int freq = 0;

int data1 = 0;
int data2 = 0;
int data3 = 0;

//variables for frequency pot monitoring
int frequency;
int freqCurrent;
unsigned int freqscaled;

void setup() {
  
  lcd.begin(16,2);
  lcd.print ("19UEC161");
  lcd.setCursor(0,1);
  lcd.print ("DL PROJECT 02");
  
  //  Set port/pin mode
  DDRD = 0xFF;        // all outputs PINS 0-7
  DDRC = 0x00;        // all inputs PINS A0-A5
  DDRB = 0xFF;        // all outputs PINS 8-13

  //  Initialize variables
  frequency = analogRead(A4);       //  initialize frequency
  freqscaled = 48*frequency+1;      //  from 1 to 48,001\
  period = samplerate/freqscaled;
   
  delay (3000);                     // So we can see the nice splash screen
  lcd.setCursor(0,0);
  lcd.print("Wave:           ");
  lcd.setCursor(0,1);
  lcd.print("     kHz        ");


  // Generate the date of a Sine function
  float x,y; 
  for(int i=0;i<255;i++){
    x=(float)i;
    y=sin((x/255)*2*PI);
    sine[i]=int(y*128)+128;
    }
}


/*
 * @Description:  This function generate a Sine signal         
 * @input:        freq
 */
void Sine_Function(int freq){
  
  for (int i=0; i<255; i++){ 
    PORTD = sine[i]; 
    delayMicroseconds(freq); 
    }
}


/*
 * @Description:  This function generate a Triangle signal         
 */

void Triangle_Function(int freq){
  
  for (int i=0; i<255; i++){
    PORTD = i;
    delayMicroseconds(freq/10);
    //delay(FREQ/100);
    } 
   
  for (int i=255; i>0; i--){
    PORTD = i;
    delayMicroseconds(freq/10);
    //delay(FREQ/100);
    }
}

/*
 * @Description:  This function generate a saw signal         
 */
 
void Sawtooth_Function(int freq){
 
    for (int i=0; i<255; i++){ 
    PORTD = i; 
    delayMicroseconds(freq/10);  
    }
}

/*
 * @Description:  This function check the value of the input Analog 4 (A4), 
 *                which configure the frequency of the signal. 
 *                This value will be displayed by the display              
 */
void checkFreq() {
  freqCurrent = analogRead(A4);
  lcd.setCursor(0,1);
  lcd.print(1-(freqCurrent/1000.000));
}


/*
 * @Description:  This function check the value of the input Analog 0 (A0) until A3, 
 *                to determined the signal to generate. 
 *                The name of the signal will be displayed by the display              
 */

void checkShape() {

  if (digitalRead(A0)==HIGH){
    lcd.setCursor(5,0);
    lcd.print(" Triangle  ");
  }
  else if (digitalRead(A1)==HIGH){
    lcd.setCursor(5,0);
    lcd.print(" Saw       ");
  }
  else if (digitalRead(A2)==HIGH){
    lcd.setCursor(5,0);
    lcd.print(" Sine      ");
  }
  else if (digitalRead(A0)==LOW & digitalRead(A1)==LOW & digitalRead(A2)==LOW){
    lcd.setCursor(5,0);
    lcd.print("             ");
  }

}


/*****************************************************/

void loop() {

  value = analogRead(A4);
  freq = value*10;

  data1 = analogRead(A0);
  data2 = analogRead(A1);
  data3 = analogRead(A2);

  checkFreq();
  checkShape();
  
  if(data1>0){
    Triangle_Function(freq);    
  }
  else if(data2>0){
    Sawtooth_Function(freq);    
  }
  else if(data3>0){
    Sine_Function(freq);     
  }
  else if(data1<0 & data2<0 & data3<0){
    }

}

/* End */
