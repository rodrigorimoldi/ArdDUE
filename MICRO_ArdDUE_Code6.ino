//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 6 - operações com display de sete     /
//                segmentos (1 a 4 unidades)        /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: manipulação dos segmentos e escri-  /
//              tas numéricas envolvendo de 1 a 4   /
//              displays de 7 segmentos.            /
//                                                  /
//**************************************************/

// DECLARAÇÃO DE VARIÁVEIS GLOBAIS
bool ponto = 0;
uint var, seqDisp, seqPin, seqNum;

// ESTABELECIMENTO DA PINAGEM DE SEGMENTOS
byte pinoSeg[8] = { 35, 34, 33, 32, 31, 30, 29, 28 };
//              = {  a,  b,  c,  d,  e,  f,  g, dp }
//    _______
//   |   a   |
// f |       | b
//   | ______|
//   |   g   |
// e |       | c
//   |_______|
//       d

// ESTABELECIMENTO DOS DISPLAYS UTILIZADOS
byte pinoDisp[4] = { 24, 25, 26, 27 };
//               = { D0, D1, D2, D3 }

// MATRIZ DE NÚMEROS PARA CATODO COMUM
byte numero[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },  // número 0
  { 0, 1, 1, 0, 0, 0, 0 },  // número 1
  { 1, 1, 0, 1, 1, 0, 1 },  // número 2
  { 1, 1, 1, 1, 0, 0, 1 },  // número 3
  { 0, 1, 1, 0, 0, 1, 1 },  // número 4
  { 1, 0, 1, 1, 0, 1, 1 },  // número 5
  { 1, 0, 1, 1, 1, 1, 1 },  // número 6
  { 1, 1, 1, 0, 0, 0, 0 },  // número 7
  { 1, 1, 1, 1, 1, 1, 1 },  // número 8
  { 1, 1, 1, 0, 0, 1, 1 },  // número 9
};

// CONDIÇÃO INICIAL DOS SEGMENTOS (DESLIGADOS)
void apagaDisplays() {
  for (var = 0; var < 7; var++)
    digitalWrite(pinoSeg[var], HIGH);
  for (var = 0; var < 4; var++)
    digitalWrite(pinoDisp[var], LOW);
  digitalWrite(pinoSeg[7], HIGH);
}

// VARREDURA DE ACIONAMENTO POR SEGMENTO
void varreSegmentos() {
  digitalWrite(pinoDisp[0], HIGH);
  digitalWrite(pinoSeg[7], HIGH);
  for (var = 0; var < 8; var++) {
    digitalWrite(pinoSeg[var], LOW);
    digitalWrite((pinoSeg[var] + 1), HIGH);
    delay(1000);
  }
}

// ACENDE UM DISPLAY ESPECÍFICO
void acendeDisplay(uint disp) {
  seqDisp = pinoDisp[(disp - 1)];
  for (var = 0; var < 4; var++)
    digitalWrite(pinoDisp[var], LOW);
  digitalWrite(seqDisp, HIGH);
}

// ESCREVE UM NÚMERO ESPECÍFICO
void escreveNumero(uint num) {
  seqPin = pinoSeg[0];
  for (var = 0; var < 7; var++) {
    digitalWrite(seqPin, !(numero[num][var]));
    seqPin--;
  }
}

// ROTINA DE CONFIGURAÇÕES
void setup() {
  for (var = 0; var < 8; var++)
    pinMode(pinoSeg[var], OUTPUT);

  for (var = 0; var < 4; var++)
    pinMode(pinoDisp[var], OUTPUT);

  apagaDisplays();
  varreSegmentos();
  apagaDisplays();

  for (seqNum = 0; seqNum < 10; seqNum++) {
    acendeDisplay(2);
    escreveNumero(seqNum);
    ponto = !ponto;
    digitalWrite(pinoSeg[7], ponto);
    delay(1000);
  }
  apagaDisplays();
}

// ROTINA PRINCIPAL
void loop() {
  acendeDisplay(1);
  escreveNumero(0);
  delay(5);
  acendeDisplay(2);
  escreveNumero(5);
  delay(5);
  acendeDisplay(3);
  escreveNumero(8);
  delay(5);
  acendeDisplay(4);
  escreveNumero(3);
  delay(5);
}