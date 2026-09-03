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

#include <Arduino.h>  // Inclui as definições base da
                      // IDE e os cabeçalhos em C do
                      // microcontrolador SAM3X8E

#define TIMER 1000    // Base de tempo dos atrasos em
                      // milissegundos (ms)


// ROTINA DE CONFIGURAÇÕES
void setup() {
  // Habilita os clocks do PIOA (ID 11) e PIOB (ID 12)
  // escrevendo '1' nos bits 11 e 12 do registrador
  // PMC_PCER0
  // 0b00000000000000000001100000000000 = 0x00001800
  REG_PMC_PCER0 = 0b00000000000000000001100000000000; 

  // Habilita o controle do pino PA14 (RELE2 / D23)
  // escrevendo '1' no bit 14 do registrador PIO_PER
  // do PIOA
  // 0b00000000000000000100000000000000 = 0x00004000
  REG_PIOA_PER  = 0b00000000000000000100000000000000; 
  
  // Habilita o controle dos pinos PB26 (RELE1 / D22)
  // e PB27 (LED / D13) escrevendo '1' nos bits 26 e
  // 27 do PIO_PER do PIOB
  // 0b00001100000000000000000000000000 = 0x0C000000
  REG_PIOB_PER  = 0b00001100000000000000000000000000; 

  // Configura o pino PA14 como saída escrevendo '1'
  // no bit 14 do registrador PIO_OER do PIOA
  // 0b00000000000000000100000000000000 = 0x00004000
  REG_PIOA_OER  = 0b00000000000000000100000000000000; 
  
  // Configura os pinos PB26 e PB27 como saídas es-
  // crevendo '1' nos bits 26 e 27 do registrador
  // PIO_OER do PIOB
  // 0b00001100000000000000000000000000 = 0x0C000000
  REG_PIOB_OER  = 0b00001100000000000000000000000000; 

  // Desabilita o pull-up interno do pino PA14 es-
  // crevendo '1' no bit 14 do registrador PIO_PUDR
  // do PIOA
  // 0b00000000000000000100000000000000 = 0x00004000
  REG_PIOA_PUDR = 0b00000000000000000100000000000000; 
  
  // Desabilita os pull-ups internos dos pinos PB26
  // e PB27 escrevendo '1' nos bits 26 e 27 do regis-
  // trador PIO_PUDR do PIOB
  // 0b00001100000000000000000000000000 = 0x0C000000
  REG_PIOB_PUDR = 0b00001100000000000000000000000000; 
} // Encerra a função setup

// ROTINA PRINCIPAL
void loop() {
  // Aciona o pino PA14 em nível lógico alto (3.3V),
  // escrevendo '1' no bit 14 do registrador PIO_SODR
  // do PIOA
  // 0b00000000000000000100000000000000 = 0x00004000
  REG_PIOA_SODR = 0b00000000000000000100000000000000;

  // Aciona os pinos PB26 e PB27 em nível lógico alto
  // escrevendo '1' nos bits 26 e 27 do registrador
  // PIO_SODR do PIOB
  // 0b00001100000000000000000000000000 = 0x0C000000
  REG_PIOB_SODR = 0b00001100000000000000000000000000; 
  
  delay(TIMER);

  // Desliga o pino PA14 (leva a 0V) escrevendo '1'
  // no bit 14 do registrador PIO_CODR do PIOA
  REG_PIOA_CODR = 0b00000000000000000100000000000000; 
  
  // Desliga os pinos PB26 e PB27 escrevendo '1' nos
  // bits 26 e 27 do registrador PIO_CODR do PIOB
  REG_PIOB_CODR = 0b00001100000000000000000000000000; 
  
  delay(TIMER);
}
