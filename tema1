const int ledPinRed = 11; // portul pentru rosu
const int ledPinGreen = 10; //portul pentru verde
const int ledPinBlue = 9; //portul pentru albastru

const int potPinRed = A0; 
const int potPinGreen = A1;
const int potPinBlue = A2;

int potValueRed = 0; 
int potValueGreen = 0;
int potValueBlue = 0;
int ledValueRed = 0;
int ledValueGreen = 0;
int ledValueBlue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT); //Led-ul cu rosu, verde si albastru
  
  pinMode(potPinRed, INPUT);
  pinMode(potPinGreen, INPUT);
  pinMode(potPinBlue, INPUT); // Potentiometrele
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValueRed = analogRead(potPinRed);  // spunem sa ia valoarea potentiometrelor
  potValueGreen = analogRead(potPinGreen);
  potValueBlue = analogRead(potPinBlue);

  ledValueRed = potValueRed/4;    // impartima la 4 valoarea potentiometrelor sa nu lumineze "in valuri" (puteam sa folosec map dar mi se pare mai simplu asa
  ledValueGreen = potValueGreen/4;  
  ledValueBlue = potValueBlue/4;
  
  analogWrite(ledPinRed, ledValueRed);  // punem fiecare culoare sa lumineze in functie de valoarea potentiometrelor 
  analogWrite(ledPinGreen, ledValueGreen);
  analogWrite(ledPinBlue, ledValueBlue);

}
