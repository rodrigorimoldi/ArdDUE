//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 1 - manipulação de saídas digitais    /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: acionar o LED nativo da PCI do Ar-  /
//              duino DUE e dois relés para opera-  /
//              com cargas de corrente alternada.   /
//                                                  /
//**************************************************/

// DEFINIÇÃO DE PARÂMETROS
#define TIMER 250
#define LED   13
#define RELE1 22
#define RELE2 23

// ROTINA DE CONFIGURAÇÕES
void setup() {
  // Configurar o pino do LED como saída
  pinMode(LED, OUTPUT);
  pinMode(RELE1, OUTPUT);
  pinMode(RELE2, OUTPUT);
}

// ROTINA PRINCIPAL
void loop() {
  // Acionar saidas digitais no tempo do TIMER (milissegundos)
  digitalWrite(LED, HIGH);
  digitalWrite(RELE1, HIGH);
  digitalWrite(RELE2, HIGH);
  delay(TIMER);

  // Desligar saidas digitais no tempo do TIMER (milissegundos)
  digitalWrite(LED, LOW);
  digitalWrite(RELE1, LOW);
  digitalWrite(RELE2, LOW);
  delay(TIMER);
}
