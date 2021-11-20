const int dataPin = 12;
const int latchPin = 11;
const int clockPin = 10;

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

int segmentDigits[] = {
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

volatile bool swState;

int xValue = 0;
int yValue = 0;


int rightThreshold = 750;
int leftThreshold = 250;

int downThreshold = 250;
int upThreshold = 750;

bool joyMoved = false;

int number[segmentCount] = {0,0,0,0};

int index;
int digitch;

const int interval = 200;
unsigned long lastFlick = 0;

volatile unsigned long lastInterrupt = 0;

void setup() 
{
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), changeSwState, FALLING);

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for (int i = 0; i < segmentCount; i++) 
  {
    pinMode(segmentDigits[i], OUTPUT);
    digitalWrite(segmentDigits[i], LOW);
  }

  Serial.begin(9600);
}
void loop(){
  writeNumber();
//  Serial.println(swState);
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
      if (index +1 < segmentCount) 
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
    
    digitch = number[index];
    
    if(xValue < downThreshold && joyMoved == false)
    {
      if(digitch > 0)
      {
        digitch--;
      }
      else
      {
        digitch = 9;
        }
        joyMoved = true;
    }
    if(xValue > upThreshold && joyMoved == false)
    {
      if(digitch < 9) 
      {
        digitch++;
      }
      else
      {
        digitch = 0;
      }
      joyMoved = true;
    }
    if(xValue >= downThreshold && xValue <= upThreshold)
      {
        joyMoved = false;
      }
    number[index] = digitch;
  }
}

void changeSwState() 
{
  //Serial.println("here");
  if (millis() - lastInterrupt >= interval) 
  {
    //Serial.println("debounced");
    swState= !swState;
  }
 
  lastInterrupt = millis();

}



void writeReg(int digit) 
{
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, digit);

  digitalWrite(latchPin, HIGH);
}

void showDigit(int displayNumber) 
{
  for (int i = 0; i < segmentCount; i++) 
  {
    digitalWrite(segmentDigits[i], HIGH);
  }

  digitalWrite(segmentDigits[displayNumber], LOW);
}

void writeNumber()
{
  
  for (int i = 0; i < segmentCount; i++) 
  {
    
   if (i == index) 
    {
      writeReg(digitArray[number[i]] ^ dpState);
    }
    else 
    {
      writeReg(digitArray[number[i]]);
    }
    showDigit(segmentCount - i - 1);
  }
}
