#Tema 3

Pentru tema 3 a trebui sa cream un dispozitiv de ,,detectat fantome" (aka un sipozitiv care detecta campuri electormagnetice)

![photo tema 3](https://github.com/TraianV/IntroductionToRobotics/blob/main/tema3/tema3.jpg)
```
#define sample 300 

const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int segSize = 7;

int segments[segSize] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG};

byte digitMatrix[10][segSize] = 
{
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};


void displayNumber(byte digit) 
{
  for (int i = 0; i < segSize; i++) 
  {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
}
const int inputPin = A0;  ///antena
const int buzzPin = 9;    //buzzer
float val;                //salveaza informatii pt analog 5
int array1[sample];
unsigned long averaging;

void setup() 
{
  for (int i = 0; i < segSize; i++) 
  {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(inputPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{               
  for (int i = 0; i < sample; i++)
  {
    array1[i] = analogRead(inputPin);
    averaging += array1[i];
  }
  val = averaging / sample;
  analogWrite(buzzPin, val);

  val = constrain(val, 0, 10);
  if (0.0 <= val and val <= 1.0)               
  {  
    displayNumber(0);   
  }
  if (1.0 <= val and val <= 2.0)               
  {
    displayNumber(1);
  }
  if (2.0 <= val and val <= 3.0)               
  {
    displayNumber(2);    
  }
  if (3.0 <= val and val <= 4.0)               
  {
    displayNumber(3);    
  }
  if (4.0 <= val and val <= 5.0)               
  {
    displayNumber(4);    
  }
  if (5.0 <= val and val <= 6.0)               
  {
    displayNumber(5);    
  }
  if (6.0 <= val and val <= 7.0)               
  {
    displayNumber(6);    
  }  
  if (7.0 <= val and val <= 8.0)               
  {
    displayNumber(7);    
  }  
  if (8.0 <= val and val <= 9.0)               
  {
    displayNumber(8);    
  }  
  if (9.0 <= val)               
  {
    displayNumber(9);    
  }  
  val = map(val, 0, 10, 0, 255);
  averaging = 0;
}```
