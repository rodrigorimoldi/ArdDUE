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
//              porta serial, em modo misto: I/O em /
//              bare-metal (C) e Serial em Arduino. /
//                                                  /
//**************************************************/

// INCLUSÃO DE BIBLIOTECAS
#include <Arduino.h>  // Traz as definições do core
                      // Arduino (Serial, delay) e
                      // cabeçalhos C do SAM3X8E

// ROTINA DE CONFIGURAÇÕES
void setup() {
  // Utiliza a biblioteca nativa do Arduino para
  // inicializar a UART (pinos PA8/PA9) sem precisar
  // configurar o PDC ou o Baud Rate manualmente
  Serial.begin(115200); 

  // 1. HABILITAÇÃO DOS CLOCKS
  // A biblioteca Serial já habilitou a UART, o PIOA e
  // também o PIOD (em virtude do fato de os pinos de
  // comunicação - RX1/TX1, RX2/TX2 e RX3/TX3 - perten-
  // cerem a estas duas famílias de PIOs). Assim, falta
  // agora habilitar os clocks do PIOB (bit 12) e PIOC
  // (bit 13) no PMC_PCER0
  REG_PMC_PCER0 = 0b00000000000000000011000000000000; 

  // 2. CONFIGURAÇÃO DAS ENTRADAS DIGITAIS
  // (TECLAS C, D, E, F) - PIOC
  // Habilita controle PIO para as teclas E (D49/PC14),
  // D (D50/PC13), C (D51/PC12) e F (D48/PC15) escre-
  // vendo '1' nos bits 12 a 15 do PIO_PER
  REG_PIOC_PER  = 0b00000000000000001111000000000000; 
  // Define os mesmos pinos como entradas desabilitan-
  // do o driver de saída no registrador PIO_ODR do PIOC
  REG_PIOC_ODR  = 0b00000000000000001111000000000000; 
  // Desabilita os resistores de pull-up internos das
  // entradas no PIOC (equivalente ao pinMode(INPUT)
  // padrão)
  REG_PIOC_PUDR = 0b00000000000000001111000000000000; 
  // Habilita o filtro de entrada digital nos pinos
  // das teclas C, D, E e F
  REG_PIOC_IFER  = 0b00000000000000001111000000000000; 
  // Seleciona a função de Debouncing (ao invés de
  // Glitch) para estes pinos
  REG_PIOC_DIFSR = 0b00000000000000001111000000000000; 
  // Define o divisor do Slow Clock para o PIOC (valor
  // 32 no bit 5 garante ~1 ms de corte). Propósito:
  // definir o tempo de corte (limiar temporal) do fil-
  // tro digital de debounce integrado ao hardware do
  // controlador de entradas e saídas (PIOC)
  REG_PIOC_SCDR  = 0b00000000000000000000000000100000;
  
  // 3. CONFIGURAÇÃO DAS ENTRADAS DIGITAIS
  // (TECLAS A e B) - PIOB
  // Habilita controle PIO para as teclas A (D53/PB14)
  // e B (D52/PB21) escrevendo '1' nos bits 14 e 21 do
  // PIO_PER do PIOB
  REG_PIOB_PER  = 0b00000000001000000100000000000000; 
  // Define os pinos 14 e 21 como entradas desabilitan-
  // do o driver de saída no registrador PIO_ODR do PIOB
  REG_PIOB_ODR  = 0b00000000001000000100000000000000; 
  // Desabilita os resistores de pull-up internos para
  // as teclas A e B no registrador PIO_PUDR do PIOB
  REG_PIOB_PUDR = 0b00000000001000000100000000000000;
  // Habilita o circuito de filtro de entrada digital
  // nos 2 pinos escrevendo no registrador PIO_IFER
  REG_PIOB_IFER  = 0b00000000001000000100000000000000; 
  // Seleciona a função de Debouncing para os pinos A
  // e B no registrador PIO_DIFSR
  REG_PIOB_DIFSR = 0b00000000001000000100000000000000; 
  // Define o divisor do Slow Clock para o PIOC (valor
  // 32 no bit 5 garante ~1 ms de corte). Propósito:
  // definir o tempo de corte (limiar temporal) do fil-
  // tro digital de debounce integrado ao hardware do
  // controlador de entradas e saídas (PIOB)
  REG_PIOB_SCDR  = 0b00000000000000000000000000100000;
}

// ROTINA PRINCIPAL
void loop() {
  
  // Imprime estado da Tecla A (D53 / PB14)
  Serial.print("A = ");
  // Faz a leitura direta do registrador PIO_PDSR do PIOB. A operação ternária
  // (? 1 : 0) normaliza a saída do bit 14 para imprimir '1' ou '0'
  Serial.print((REG_PIOB_PDSR & 0b00000000000000000100000000000000) ? 1 : 0); 
  Serial.print("   ");

  // Imprime estado da Tecla B (D52 / PB21)
  Serial.print("B = ");
  Serial.print((REG_PIOB_PDSR & 0b00000000001000000000000000000000) ? 1 : 0); 
  Serial.print("   ");

  // Imprime estado da Tecla C (D51 / PC12)[
  Serial.print("C = ");
  Serial.print((REG_PIOC_PDSR & 0b00000000000000000001000000000000) ? 1 : 0); 
  Serial.print("   ");

  // Imprime estado da Tecla D (D50 / PC13)
  Serial.print("D = ");
  Serial.print((REG_PIOC_PDSR & 0b00000000000000000010000000000000) ? 1 : 0); 
  Serial.print("   ");

  // Imprime estado da Tecla E (D49 / PC14)
  Serial.print("E = ");
  Serial.print((REG_PIOC_PDSR & 0b00000000000000000100000000000000) ? 1 : 0); 
  Serial.print("   ");

  // Imprime estado da Tecla F (D48 / PC15)
  Serial.print("F = ");
  Serial.print((REG_PIOC_PDSR & 0b00000000000000001000000000000000) ? 1 : 0); 
  Serial.print("   ");

  // Quebra a linha na porta serial utilizando o recurso nativo da biblioteca
  // do Arduino
  Serial.println();
  delay(250); 
}
