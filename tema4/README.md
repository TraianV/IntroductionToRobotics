#Tema 4

Pentru tema 4 a trebuit sa manipulam cifrele unui 4 digit 7 - segment display cu un joystick.
```
const int dataPin = 12;
const int latchPin = 11;
const int clockPin = 10;
//shift register
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
//4 digit 7 - segmet display
bool dpState; // starile care desemneaza daca se alege o cifra din cele patru si valorile lor.

const int pinX = A0;
const int pinY = A1;
const int pinSW = 3;  

int xValue = 0;
int yValue = 0;

volatile bool swState;

int rightThreshold = 750;
int leftThreshold = 250;

int downThreshold = 250;
int upThreshold = 750;

bool joyMoved = false;
// joystick

int number[segmentCount] = {0,0,0,0};//numarul care se retine pentru a fi afisat pe 4 digit 7 - segment display

int index; //variabila care retine actuala cifra ce poate fi editata
int digitch; // variabila ce ajuta la editarea unei cifre

const int interval = 200;
unsigned long lastFlick = 0;  

volatile unsigned long lastInterrupt = 0;
//pentru a nu folosi delay

void setup() 
{
  pinMode(pinSW, INPUT_PULLUP);//buttonl de pe joystick
  attachInterrupt(digitalPinToInterrupt(pinSW), changeSwState, FALLING); // interrupt, 
  //cand este apasat butonul se pe joystick se trece in starea de editarea a unei cifre selectate
  //se apasa din nou pentru a se reintoarce in starea de selectie a cifrei

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 

  for (int i = 0; i < segmentCount; i++) 
  {
    pinMode(segmentDigits[i], OUTPUT);//4 digit 7 - segment display
    digitalWrite(segmentDigits[i], LOW);
  }

  Serial.begin(9600);
}
void loop(){
  writeNumber();
//  Serial.println(swState);
  if(swState == HIGH)//in starea HIGH se selecteaza cifra 
  {
    yValue = analogRead(pinY);
     if(millis() - lastFlick >= interval) //punctul de la digit care clipoceste arata actuala cifra de selectat
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
//daca joystick-ul e rotit in drapta indexul selecteaza cifra din dreapata celei curente, daca se roteste dreapata dupa cifra a patra se reintoarce la prima cifra
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
    }//analog daca se roteste joysticul in stanga, se selcteaza cifra din stanga, daca se roteste stanga inainte de prima cifra se reintoarce la a patra cifra
    
    if (leftThreshold <= yValue && yValue <= rightThreshold) 
    {
      joyMoved = false;
    } 
  }
  else altfel se editeaza cifra selctata
  {
    xValue = analogRead(pinX);
    dpState = HIGH; punctul se aprinde continuu
    
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
    }// roteste in jos pentru a scadea cifra iar daca scade sub 0 se intoarce la 9
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
    }// roteste in sus pentru a creste cifra iar daca creste peste 9 se intoarce la 0
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
    swState= !swState;//interrupt care schimba starea
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


```
[Video1]("https://drive.google.com/file/d/1jj_fa7Nc97I1eoLay6ZzlInsVy1I1G74/view?usp=sharing")
