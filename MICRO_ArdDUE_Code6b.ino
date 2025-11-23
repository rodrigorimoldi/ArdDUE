//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 6b - operações com display de sete    /
//                 segmentos empregando o módulo    /
//                 TM1637.                          /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: manipulação dos segmentos e escri-  /
//              tas numéricas envolvendo de 1 a 4   /
//              displays de 7 segmentos através da  /
//              biblioteca pública do módulo inte-  /
//              grado TM1637. Funcionalidades:      /
//                  1. Exibe uma animação entre os  /
//                     os segmentos;                /
//                  2. Exibe uma sequência numérica /
//                     (0 a 9) em cada dígito a ca- /
//                     da 500ms;                    /
//                  3. Exibe uma contagem rápida de /
//                     0000 a 9999;                 /
//                  4. Exibe um número com ponto,   /
//                     podendo ser 1 ou 2 pontos de /
//                     acordo com o modelo usado;   /
//                  5. Exibe um valor hipotético de /
//                     temperatura.                 /
//**************************************************/

// INCLUSÃO DA BIBLIOTECA DO MÓDULO
#include <TM1637Display.h>

// DEFINIÇÃO DOS PINOS DE COMUNICAÇÃO COM O MÓDULO
#define CLK 35  // Pino Clock conectado ao pino digital 2
#define DIO 34  // Pino Data I/O conectado ao pino digital 3

// CRIAÇÃO DO OBJETO DISPLAY
TM1637Display display(CLK, DIO);

// CRIAÇÃO DO SÍMBOLO "°C" PARA INDICAÇÃO DE TEMPERATURA
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // °
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};


// ROTINA DE CONFIGURAÇÕES
void setup() {
  // Define o brilho do display
  // (0 a 7, onde 7 é o mais brilhante)
  display.setBrightness(5);
  
  // Limpa completamente o display
  display.clear();
  delay(1000);
}


// ROTINA PRINCIPAL
void loop() {
  // PARTE 1: Animação loading
  animacaoLoading();
  delay(2000);
    
  // PARTE 2: Sequência numérica individual em cada dígito
  sequenciaPorDigito();
  delay(2000);
  
  // PARTE 3: Contagem rápida de 0000 a 9999
  contagemRapida();
  delay(2000);

  // PARTE 4: Número com ponto (ou dois pontos)
  nroComPonto();
  delay(2000);

  // PARTE 5: Temperatura (neste caso, nenhum sensor)
  temperatura();
  delay(2000);
}


// FUNÇÃO PARA CRIAR A ANIMAÇÃO LOADING
// Apenas para gerar uma ação dinâmica no display
void animacaoLoading() {
  uint8_t segmentos[] = {
    SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F};
  for (int i = 0; i < 6; i++) {
    display.setSegments(&segmentos[i], 1, 0);
    delay(100);
  }
}


// FUNÇÃO PARA SEQUENCIAMENTO DE DIGITOS
// Exibe números de 0 a 9 sequencialmente em cada dígito
// Intervalo: 500ms (meio segundo) entre cada número
void sequenciaPorDigito() {
  // Array para controlar os 4 dígitos (posições 0, 1, 2, 3)
  // Inicialmente todos apagados
  uint8_t dados[4] = {0x00, 0x00, 0x00, 0x00};
  
  // Loop para escrita em cada dígito
  // (0 = mais à esquerda, 3 = mais à direita)
  for (int digito = 0; digito < 4; digito++) {
    
    // Loop para escrita de cada número (0 a 9)
    for (int num = 0; num <= 9; num++) {
      // Codifica o número para o formato do display
      dados[digito] = display.encodeDigit(num);
      
      // Exibe os dados no display
      display.setSegments(dados);
      
      // Aguarda meio segundo
      delay(500);
    }
    
    // Limpa o dígito atual após a sequência
    dados[digito] = 0x00;
  }
  
  // Limpa todo o display
  display.clear();
}


// FUNÇÃO PARA CONTAGEM RÁPIDA SEQUENCIAL
// Exibe contagem de 0000 até 9999 usando todos os 4 dígitos
// Velocidade: aproximadamente 50ms por número
void contagemRapida() {
  // Contagem de 0 a 9999
  for (int contador = 0; contador <= 9999; contador++) {
    // Exibe o número no display
    // Parâmetros: número, leading_zeros (false = não mostrar zeros à esquerda)
    display.showNumberDec(contador, true); // true = mostra zeros à esquerda (0001, 0002, etc.)
    
    // Intervalo entre números (50ms = contagem rápida)
    delay(50);
  }
  
  // Pisca o display 3 vezes ao finalizar
  for (int i = 0; i < 3; i++) {
    display.clear();
    delay(200);
    display.showNumberDec(9999, true);
    delay(200);
  }
  
  display.clear();
}


// FUNÇÃO PARA EXIBIÇÃO DE NÚMERO COM PONTO
// A representação do ponto depende do modelo de display
void nroComPonto() {
  // Exibir 12.34 ou 12:34 (dependendo do modelo adquirido)
  display.showNumberDecEx(1234, 0b01000000, false);
  // O segundo parâmetro controla os pontos:
  // 0b01000000 = pontos após o 2º dígito
  delay(2000);
}


// FUNÇÃO PARA EXIBIR TEMPERATURA
void temperatura() {
  int temperatura = 23; // Ou a leitura do sensor
  display.showNumberDec(temperatura, false, 2, 0);
  display.setSegments(celsius, 2, 2);
  delay(2000);
}
