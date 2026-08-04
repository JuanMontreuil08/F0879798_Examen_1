#include <Arduino.h> // Compilar en Wokwi

// Pines de los pulsadores
const int SW1 = 18;
const int SW2 = 17;

// Pin del potenciometro
const int POTENCIOMETRO = 34;

// Pines del LED RGB
const int LED_AZUL = 25;
const int LED_VERDE = 26;
const int LED_ROJO = 27;

void apagarLED() {
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AZUL, LOW);
}

void parpadearColor(int pinColor, int tiempoRetardo) {
  for (int i = 0; i < 3; i++) {
    // Encender solamente el color seleccionado
    apagarLED();
    digitalWrite(pinColor, HIGH);
    delay(tiempoRetardo);

    // Apagar durante el mismo intervalo
    apagarLED();
    delay(tiempoRetardo);
  }
}

void ejecutarSecuencia(int boton) {
  int valorPotenciometro = analogRead(POTENCIOMETRO);
  int tiempoRetardo = map(valorPotenciometro, 0, 4095, 1000, 4000);

  Serial.println("-------------------------");

  if (boton == 1) {
    Serial.println("Boton presionado: SW1");
  } else {
    Serial.println("Boton presionado: SW2");
  }

  Serial.print("Valor del potenciometro: ");
  Serial.println(valorPotenciometro);

  Serial.print("Tiempo de retardo: ");
  Serial.print(tiempoRetardo);
  Serial.println(" ms");

  // Seleccionar la secuencia segun el boton presionado
  if (boton == 1) {
    // SW1: rojo -> verde -> azul
    parpadearColor(LED_ROJO, tiempoRetardo);
    parpadearColor(LED_VERDE, tiempoRetardo);
    parpadearColor(LED_AZUL, tiempoRetardo);
  } else {
    // SW2: azul -> verde -> rojo
    parpadearColor(LED_AZUL, tiempoRetardo);
    parpadearColor(LED_VERDE, tiempoRetardo);
    parpadearColor(LED_ROJO, tiempoRetardo);
  }

  apagarLED();
  Serial.println("Secuencia finalizada");
}

void setup() {
  Serial.begin(115200);

  // Resolucion de 12 bits: valores entre 0 y 4095
  analogReadResolution(12);

  // Los botones estan conectados entre el GPIO y GND
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  // El LED debe iniciar apagado
  apagarLED();

  Serial.println("Sistema iniciado");
  Serial.println("Esperando SW1 o SW2...");
}

void loop() {
  if (digitalRead(SW1) == LOW) {
    ejecutarSecuencia(1);

    // Esperar a que el usuario suelte el boton
    while (digitalRead(SW1) == LOW) {
      delay(10);
    }

    delay(50);
  } else if (digitalRead(SW2) == LOW) {
    ejecutarSecuencia(2);

    // Esperar a que el usuario suelte el boton
    while (digitalRead(SW2) == LOW) {
      delay(10);
    }

    delay(50);
  }
}
