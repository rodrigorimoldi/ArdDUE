//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 2 - Entradas e Debounce em Hardware   /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: Ler uma tecla tátil com debounce    /
//              nativo em hardware e acionar um     /
//              relé em resposta.                   /
//                                                  /
//**************************************************/

#include <Arduino.h>

// ROTINA DE CONFIGURAÇÕES
void setup() {
  // Habilita os clocks do PIOA (ID 11) e PIOB (ID 12)
  // escrevendo '1' nos bits 11 e 12 do registrador
  // PMC_PCER0
  // 0b00000000000000000001100000000000 = 0x00001800
  REG_PMC_PCER0  = 0b00000000000000000001100000000000; 

  // 2. CONFIGURAÇÃO DA SAÍDA (RELÉ NO PINO D22 -> PB26)
  // Habilita o controle do pino PB26 escrevendo '1' no
  // bit 26 do registrador PIO_PER do PIOB
  // 0b00000100000000000000000000000000 = 0x04000000
  REG_PIOB_PER   = 0b00000100000000000000000000000000;

  // Configura o pino PB26 como saída digital escrevendo
  // '1' no bit 26 do registrador PIO_OER do PIOB
  // 0b00000100000000000000000000000000 = 0x04000000
  REG_PIOB_OER   = 0b00000100000000000000000000000000; 

  // 3. CONFIGURAÇÃO DA ENTRADA
  // (TECLA TÁTIL NO PINO D24 -> PA15)
  // Habilita o controle do pino PA15 escrevendo '1' no
  // bit 15 do registrador PIO_PER do PIOA
  // 0b00000000000000001000000000000000 = 0x00008000
  REG_PIOA_PER   = 0b00000000000000001000000000000000;

  // Configura o pino PA15 como entrada (desabilitando
  // a saída) escrevendo '1' no bit 15 do registrador
  // PIO_ODR do PIOA
  // 0b00000000000000001000000000000000 = 0x00008000
  REG_PIOA_ODR   = 0b00000000000000001000000000000000;

  // Ativa o resistor de pull-up interno no pino PA15
  // escrevendo '1' no bit 15 do registrador PIO_PUER
  // do PIOA
  // 0b00000000000000001000000000000000 = 0x00008000
  REG_PIOA_PUER  = 0b00000000000000001000000000000000; 

  // 4. CONFIGURAÇÃO DO DEBOUNCE EM HARDWARE
  // Habilita o circuito de filtro no pino PA15 escre-
  // vendo '1' no bit 15 do Input Filter Enable Register
  // (PIO_IFER)
  // 0b00000000000000001000000000000000 = 0x00008000
  REG_PIOA_IFER  = 0b00000000000000001000000000000000;

  // Seleciona a função "Debouncing" (ao invés de
  // "Glitch") escrevendo '1' no bit 15 do Debouncing
  // Input Filter Select Register (PIO_DIFSR)
  REG_PIOA_DIFSR = 0b00000000000000001000000000000000;

  // Define o divisor do Slow Clock (SCDR) para deter-
  // minar o tempo de corte do filtro de debounce.
  // Escrevendo o valor 32 (bit 5 em '1') no PIO_SCDR
  // do PIOA para obter um atraso de estabilização
  // de ~1 ms
  REG_PIOA_SCDR  = 0b00000000000000000000000000100000; 
} // Encerra a função setup

// ROTINA PRINCIPAL
void loop() {
  
  // A leitura digital exige verificar se o bit 15 do Pin
  // Data Status Register (PIO_PDSR) está em nível baixo '0'
  // (tecla pressionada)
  // Para isolar o pino 15 de todos os outros 31 pinos da porta,
  // usa-se o "E" lógico (&) com uma máscara onde apenas o bit
  // 15 é '1'
  if ((REG_PIOA_PDSR & 0b00000000000000001000000000000000) == 0) { 
    // Caso o botão esteja pressionado (0V lido no pino com
    // pull-up):
    // Aciona o pino PB26 (Relé D22) escrevendo '1' no bit 26
    // do registrador PIO_SODR do PIOB
    REG_PIOB_SODR = 0b00000100000000000000000000000000; 
  } else { 
    // Caso o botão esteja solto (3.3V lidos devido ao resis-
    // tor de pull-up):
    // Desliga o pino PB26 escrevendo '1' no bit 26 do regis-
    // trador PIO_CODR do PIOB
    REG_PIOB_CODR = 0b00000100000000000000000000000000; 
  }
}
