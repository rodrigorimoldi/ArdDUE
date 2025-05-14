//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 10 - sensoriamento de sinais de tem-  /
//                 peratura, umidade e ultrassom    /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: manipular os sinais correspondentes /
//              às grandezas físicas supramenciona- /
//              das provenientes da Shield HC-SR04  /
//              (ultrassom) e do sensor DHT-11 (u-  /
//              midade e temperatura).
//                                                  /
//**************************************************/

// INCLUSÃO DE BIBLIOTECAS
#include <DHT.h>
#include "Ultrasonic.h"

// DEFINIÇÃO DE PARÂMETROS
#define Trig    11
#define Echo    12
#define DHTPIN  13    // Pino conectado ao sinal do DHT11
#define DHTTYPE DHT11 // Define o tipo do sensor

// ESTABELECIMENTO DA PINAGEM DOS SENSORES
Ultrasonic ultrasonic(Trig, Echo);
DHT dht(DHTPIN, DHTTYPE);

// ROTINA DE CONFIGURAÇÕES
void setup() {
  Serial.begin(115200);
  dht.begin();
}

// ROTINA PRINCIPAL
void loop() {
  // Aguarda tempo entre leituras
  delay(1000);

  // Lê os valores de umidade, temperatura e distância
  float umidade = dht.readHumidity();         // Em %
  float temperatura = dht.readTemperature();  // Em °C
  uint  distancia = ultrasonic.read(CM);      // Em cm

  // Verifica se a leitura do sensor DHT11 falhou
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Erro ao ler do sensor DHT11.");
    return;
  }

  // Exibe os dados no monitor serial
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println("%");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");
  Serial.println();

  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println("cm");
}
