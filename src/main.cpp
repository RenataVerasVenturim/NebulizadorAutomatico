#include <Arduino.h>
#include <DHT.h>

#define DHTPIN D1         // Pino do sensor DHT
#define DHTTYPE DHT11     // Tipo de sensor DHT
#define RELAYPIN D2       // Pino de controle do relé

DHT dht(DHTPIN, DHTTYPE); // Inicializa o sensor DHT

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Configura o pino do relé como saída
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW); // Relé começa desligado
}

void loop() {
  // Lê a umidade e a temperatura
  float h = dht.readHumidity();    
  float t = dht.readTemperature(); 

  // Verifica se houve erro ao ler os valores
  if (isnan(h) || isnan(t)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  }

  // Exibe as leituras no Serial Monitor
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" °C\tUmidade: ");
  Serial.print(h);
  Serial.println(" %");

  // Lógica para controlar o relé com base na umidade
  if (h < 74) {
    digitalWrite(RELAYPIN, LOW);  // Liga o nebulizador
    Serial.println("Nebulizador LIGADO");
  } else {
    digitalWrite(RELAYPIN, HIGH);   // Desliga o nebulizador
    Serial.println("Nebulizador DESLIGADO");
  }

  delay(2000); // Aguarda 2 segundos antes da próxima leitura
}
