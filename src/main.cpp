// Blibliotevas nescessárias
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
// Definir as variavéis nescessárias
#define buzzer 11
#define bnt 12
int leds = 12;
unsigned int level=0;
int led =0;
// Objeto
Adafruit_NeoPixel fita(leds, 13);
// Prototipação das funções
void vitoria();
void derrota();
void mlevel();

void setup() {
  fita.begin();
  fita.setBrightness(100);
  fita.show(); 
  pinMode(buzzer, OUTPUT);  
  pinMode(bnt, INPUT_PULLUP);
  mlevel();
  randomSeed(analogRead(0)); //fonte para a função random poder funcionar com números pseudos aleatórios
  led = random(0, 12);
}

void loop() {
  for (int i = 0; i < leds; i++) { // roleta dos leds
    delay(150);
    fita.clear(); 
    fita.setPixelColor(i, fita.Color(0, 255, 0)); 
    bool in = !digitalRead(bnt);
    if(in && (i == led)){ //gatilho do level up
      vitoria();
      level++;
      mlevel();
    }else if(in && (i != led)){ // gatilho do level down
      derrota();
      level--;
      mlevel();
      led = random(0, 12);
    }
    if(i == (led-1)){// por algum motivo para mostrar é led -1 
      fita.setPixelColor(i, fita.Color(255, 0, 0)); // indica o led a ser apertado
    }
    fita.show();
  }
}
void vitoria(){
  tone(buzzer, 523, 200); // Nota C5 por 200ms
  delay(200);
  tone(buzzer, 659, 200); // Nota E5 por 200ms
  delay(200);
  tone(buzzer, 784, 300); // Nota G5 por 300ms
  delay(300);
  tone(buzzer, 523, 200); // Nota C5 por 200ms
  delay(200);
  tone(buzzer, 659, 200); // Nota E5 por 200ms
  delay(200);
  tone(buzzer, 784, 300); // Nota G5 por 300ms
  delay(300);
}
void derrota(){
  tone(buzzer, 784, 200); // Nota G5 por 200ms
  delay(200);
  tone(buzzer, 659, 200); // Nota E5 por 200ms
  delay(200);
  tone(buzzer, 523, 300); // Nota C5 por 300ms
  delay(300);
  tone(buzzer, 784, 200); // Nota G5 por 200ms
  delay(200);
  tone(buzzer, 659, 200); // Nota E5 por 200ms
  delay(200);
  tone(buzzer, 523, 300); // Nota C5 por 300ms
  delay(300);
}

void mlevel(){
  fita.clear(); 
  for(int i=0; i < level; i++){ // exibe a dificuldade atual 
    fita.setPixelColor(i, fita.Color(0, 0, 255));
  }
  if(level == leds){
    fita.clear();
    fita.rainbow();
    level = 0;
  }
  fita.show();
  delay(500);
}