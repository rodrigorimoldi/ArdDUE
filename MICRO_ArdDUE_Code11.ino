//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 11 - manipulação de rotinas de inter- /
//                 rupção (ISR) - parte 1           /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: utilização da interrupção externa   /
//              (aplicável em qualquer pino digital /
//              do DUE) como controlador do LED in- /
//              terno (pino 13) da PCI do Arduino   /
//              DUE.                                /
//                                                  /
//**************************************************/

// DEFINIÇÃO DE PARÂMETROS
#define LED 13
#define TECLA_A 53

bool estado = LOW;

void pisca() {
  estado = !estado;
}

// ROTINA DE CONFIGURAÇÕES
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(TECLA_A, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TECLA_A), pisca, RISING);
}

void loop() {
  digitalWrite(LED, estado);
}