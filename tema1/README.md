# Tema 1

Am avut de facut cu ajutorul placii Anduino uno sa facem sa lumineze un led RGB cu 3 potentiometre, unul pentru fiecare culoare.
La inceput am luat porturile digitale 11, 10 si 9 pentru cuorile led-ului (11 pentru rosu, 10 pentru verde, 9 pentru albastru).

```
const int ledPinRed = 11; // portul pentru rosu
const int ledPinGreen = 10; //portul pentru verde
const int ledPinBlue = 9; //portul pentru albastru
```
Apoi am luat porturile analog A0, A1, A2 pentru potentiometre si am decis ca cel care transmite informatia catre A0 sa fie pentru rosu, A1 pentru verde si A2 pentru albastru.
```
const int potPinRed = A0; 
const int potPinGreen = A1;
const int potPinBlue = A2;
```
Mai departe am declarat variabilele potValue si ledValue pentru fiecare culoare. potValue va retine valoarea potentiometrelor iar ledValue va fi potValue / 4 pentru ca valoarea maxima a potentiometrelor este 1023 iar valoarea maxima a led-ului este 255, daca valoarea trece de 255 led-ul va lua valoarea potentiometrului %256 ( la 256 va fi aporape stins, ca la valoarea 0, la 510 va fi ca la 255, la 601 va fi ca la 100 etc.)  .
```
int potValueRed = 0; 
int potValueGreen = 0;
int potValueBlue = 0;

int ledValueRed = 0;
int ledValueGreen = 0;
int ledValueBlue = 0;
```
In functia setup declaram culorile led-ului ca fiind date de iesire (daca vrem sa lumineze nu trebuie sa interactionam fizic cu led-ul) si potentiometrele sunt date de intrare (interactionam fizic pentru a schimba valoarea led-ului ca fiecare culoare sa lumineze mai mult sau mai putin). 
```
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT); //Led-ul cu rosu, verde si albastru
  
  pinMode(potPinRed, INPUT);
  pinMode(potPinGreen, INPUT);
  pinMode(potPinBlue, INPUT); // Potentiometrele
}
```
In functia loop spunem variabilelor potValue sa tina minte valoarea potentiometrelor iar variabilele ledValue le imparte la 4.
```
void loop() {
  // put your main code here, to run repeatedly:
  potValueRed = analogRead(potPinRed); 
  potValueGreen = analogRead(potPinGreen);
  potValueBlue = analogRead(potPinBlue);

  ledValueRed = potValueRed/4;
  ledValueGreen = potValueGreen/4;  
  ledValueBlue = potValueBlue/4;
  """
  In final culorile led-ului se activeaza in functie de valorile potentiometrelor.
  """
  analogWrite(ledPinRed, ledValueRed);
  analogWrite(ledPinGreen, ledValueGreen);
  analogWrite(ledPinBlue, ledValueBlue);

}
```
