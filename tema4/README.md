```
#include <EEPROM.h>

const int dataPin = 12;
const int latchPin = 11;
const int clockPin = 10;

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int segmentDigits[] = {
  segD1, segD2, segD3, segD4
};
const int segmentCount = 4;

int digitArray[16] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

bool dpState;



const int pinX = A0;
const int pinY = A1;

const int pinSW = 3;
bool swState = HIGH;

int xValue = 0;
int yValue = 0;


int rightThreshold = 750;
int leftThreshold = 250;

int downThreshold = 250;
int upThreshold = 750;

bool joyMoved = false;

int number[segmentCount] = {0, 0, 0, 0};

int index = 0;

const int interval = 500;
unsigned long lastFlick = 0;

void setup(){
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), changeSwState, FALLING);
  
  pinMode(dataPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  
  for(int i=0;i<segmentDigits[i];i++)
  {
    pinMode(segmentDigits[i],OUTPUT);
    digitalWrite(segmentDigits[i],LOW);
  }
  loadState();
  Serial.begin(9600);
}
void loop(){
  
  writeNumber();
  if(swState == HIGH)
  {
    yValue = analogRead(pinY);
     if(millis() - lastFlick >= interval)
    {
      dpState = !dpState;
      lastFlick = millis();
    }
    
    if (yValue > rightThreshold && joyMoved == false)
    {
      if (index + 1 < segmentCount) 
      {
        index++;
      }
      else 
      {
        index = 0;
      }
      joyMoved = true;
    }

    if (yValue < leftThreshold && joyMoved == false)
    {
        if (index > 0) 
        {
          index--;
        }
         else 
        {
          index = segmentCount - 1;
        }
        joyMoved = true;
    }
    
    if (leftThreshold <= yValue && yValue <= rightThreshold) 
    {
      joyMoved = false;
    } 
  }
  else
  {
    xValue = analogRead(pinX);
    dpState = HIGH;
    
    int digit = number[index];
    
    if(xValue < downThreshold && joyMoved == false)
    {
    if(digit >0)
      {
        digit--;
      }
      else
      {
        digit =9;
        }
        joyMoved = true;
    }
    if(xValue > upThreshold && joyMoved == false)
    {
      if(digit <9) 
      {
        digit++;
      }
      else
      {
        digit =0;
      }
      joyMoved = true;
    }
    if(xValue >= downThreshold && xValue <= upThreshold)
      {
        joyMoved = false;
      }
    number[index] = digit;
    
  }
}
void writeReg(int digit){
  
  digitalWrite(latchPin,LOW);
  
  shiftOut(dataPin,clockPin,MSBFIRST,digit);
  
  digitalWrite(latchPin, HIGH);
  
}
void showDigit(int digitNumber)
{
  for(int i=0;i < segmentCount; i++){
    
    digitalWrite(segmentDigits[i],HIGH);
    
  }
  
  digitalWrite(segmentDigits[digitNumber],LOW);
  
}

void changeSwState() 
{
  static unsigned long lastInterrupt = 0;
  unsigned long interrupt = millis();

  if (interrupt - lastInterrupt >= interval) 
  {
    saveState(index);
    swState = !swState;
  }
 
  lastInterrupt = interrupt;

}

void writeNumber()
{
  
  for (int i = 0; i < segmentCount; i++)
  {
    showDigit(segmentCount - i - 1);
  }
}


int getCurrentNumber() 
{
  int nr = 0;
  for (int i = 0; i < segmentCount; i++) 
  {
    nr = nr * 10 + number[i];
  }
  return nr;
}


void setCurrentNumber(int currentNumber) 
{
  for (int i = segmentCount - 1; i >= 0; i--) 
  {
    number[i] = currentNumber % 10;
    currentNumber /= 10;
  }
}


void saveState(int i) {
  EEPROM.write(i, number[i]);
  EEPROM.write(segmentCount, i);
}



void loadState() {
  for (int i = 0; i < segmentCount; ++ i) {
    number[i] = EEPROM.read(i);
  }
}
```
