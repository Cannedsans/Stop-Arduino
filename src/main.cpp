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
    if(in && (i == led+1)){ //gatilho do level up
      vitoria();
      level++;
      mlevel();
    }else if(in && (i != led+1)){ // gatilho do level down
      derrota();
      --level;
      if(level > 12){
        level =0;
      }
      mlevel();
      led = random(0, 12);
    }
    if(i == (led)){ // por algum motivo fica 1 led depois no núemro correto
      fita.setPixelColor(i, fita.Color(255, 0, 0)); // indica o led a ser apertado
    }
    fita.show();
  }
}
void vitoria() {
  tone(buzzer, 262, 200); // Nota C4 por 200ms (uma oitava abaixo de C5)
  delay(200);
  tone(buzzer, 329, 200); // Nota E4 por 200ms
  delay(200);
  tone(buzzer, 392, 300); // Nota G4 por 300ms
  delay(300);
  tone(buzzer, 262, 200); // Nota C4 por 200ms
  delay(200);
  tone(buzzer, 329, 200); // Nota E4 por 200ms
  delay(200);
  tone(buzzer, 392, 300); // Nota G4 por 300ms
  delay(300);
}

void derrota() {
  tone(buzzer, 392, 200); // Nota G4 por 200ms
  delay(200);
  tone(buzzer, 329, 200); // Nota E4 por 200ms
  delay(200);
  tone(buzzer, 262, 300); // Nota C4 por 300ms
  delay(300);
  tone(buzzer, 392, 200); // Nota G4 por 200ms
  delay(200);
  tone(buzzer, 329, 200); // Nota E4 por 200ms
  delay(200);
  tone(buzzer, 262, 300); // Nota C4 por 300ms
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
    fita.show();
    delay(3000);
    return;
  }
  fita.show();
  delay(500);
}