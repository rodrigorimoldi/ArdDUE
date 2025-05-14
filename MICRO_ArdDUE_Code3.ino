//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 3 - manipulação de entradas digitais  /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: identificação das teclas pressiona- /
//              das através de comandos enviados à  /
//              porta serial.                       /
//                                                  /
//**************************************************/

// DEFINIÇÃO DE PARÂMETROS
#define TECLA_A 53  // azul
#define TECLA_B 52  // verde
#define TECLA_C 51  // amarelo
#define TECLA_D 50  // laranja
#define TECLA_E 49  // vermelho
#define TECLA_F 48  // marrom

// ROTINA DE CONFIGURAÇÕES
void setup() {
  Serial.begin(115200);

  pinMode(TECLA_A, INPUT);
  pinMode(TECLA_B, INPUT);
  pinMode(TECLA_C, INPUT);
  pinMode(TECLA_D, INPUT);
  pinMode(TECLA_E, INPUT);
  pinMode(TECLA_F, INPUT);
}

// ROTINA PRINCIPAL
void loop() {
  Serial.print("A = ");
  Serial.print(digitalRead(TECLA_A));
  Serial.print("   ");

  Serial.print("B = ");
  Serial.print(digitalRead(TECLA_B));
  Serial.print("   ");

  Serial.print("C = ");
  Serial.print(digitalRead(TECLA_C));
  Serial.print("   ");

  Serial.print("D = ");
  Serial.print(digitalRead(TECLA_D));
  Serial.print("   ");

  Serial.print("E = ");
  Serial.print(digitalRead(TECLA_E));
  Serial.print("   ");

  Serial.print("F = ");
  Serial.print(digitalRead(TECLA_F));
  Serial.print("   ");

  Serial.println();
}
