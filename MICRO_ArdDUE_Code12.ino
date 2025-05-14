//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 12 - manipulação de rotinas de inter- /
//                 rupção (ISR) - parte 2           /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: utilização da interrupção de timer  /
//              TC0 (apenas o canal 0) para criar   /
//              um cronômetro progressivo de 3 mi-  /
//              nutos com exibição de resultados na /
//              tela do GLCD 128x64.
//                                                  /
//**************************************************/

// INCLUSÃO DE BIBLIOTECAS
#include "U8g2lib.h"

#ifdef U8X8_HAVE_HW_SPI
#include "SPI.h"
#endif
#ifdef U8X8_HAVE_HW_I2C
#include "Wire.h"
#endif

// DEFINIÇÃO DA PINAGEM DO DISPLAY GRÁFICO LCD 128x64
// u8g2(U8G2_R0, E, R/W, D/I, RST)
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, 39, 38, 37, 36);

// VARIÁVEIS DO CRONÔMETRO
volatile int segundos = 0;
volatile bool atualizar = false;

// ROTINA DE CONFIGURAÇÕES
void setup() {
  u8g2.begin();
  configurarTimer();  // 1Hz = 1 interrupção por segundo
  exibirTempo(0, 0);
}

// ROTINA PRINCIPAL
void loop() {
  if (atualizar) {
    atualizar = false;

    int minutos = segundos / 60;
    int segs = segundos % 60;  // Resto da divisão

    exibirTempo(minutos, segs);

    if (segundos <= 180) {
      segundos++;
    } else {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_fub14_tf);
      u8g2.drawStr(25, 25, "TEMPO");
      u8g2.drawStr(6, 50, "ESGOTADO");
      u8g2.sendBuffer();

      NVIC_DisableIRQ(TC0_IRQn);
    }
  }
}

// FUNÇÃO DE EXIBIÇÃO
void exibirTempo(int min, int seg) {
  char buffer[16];
  sprintf(buffer, "%02d:%02d", min, seg);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_spleen5x8_mf);
  u8g2.setCursor(0, 8);
  u8g2.print("CRONOMETRO PROGRESSIVO");
  u8g2.setFont(u8g2_font_fub35_tf);
  u8g2.drawStr(0, 55, buffer);
  u8g2.sendBuffer();
}

// CONFIGURAÇÃO DO TIMER TC0, canal 0
void configurarTimer() {
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC0);

  //********************************************//
  // Passos de configuração do timer:           //
  //                                            //
  // 1) Identificação do clock principal do MCU.//
  //      * Para o Arduino DUE, MCK = 84 MHz    //
  //      * MCK (Main Clock)                    //
  //                                            //
  // 2) Definir a frequência de temporização    //
  //    (FT) do timer utilizado (prescaler),   //
  //    observando as seguintes possibilidades: //
  //      * TIMER_CLOCK1 (MCK / 2)              //
  //      * TIMER_CLOCK2 (MCK / 8)              //
  //      * TIMER_CLOCK3 (MCK / 32)             //
  //      * TIMER_CLOCK4 (MCK / 128)            //
  //      * TIMER_CLOCK5 (MCK / 1024)           //
  //                                            //
  // 3) Definir o modo de operação da interrup- //
  //    ção aplicado ao registrador interno     //
  //    TC_CMR (Channel Mode Register). As pos- //
  //    sibilidades existentes são:             //
  //      * Modo WAVE - usado para gerar sinais //
  //        periódicos, sinais PWM ou delays    //
  //        precisos;                           //
  //      * Modo CAPTURE - usado para medir si- //
  //        nais externos (frequência, largura  //
  //        de pulso, etc.), permitindo regis-  //
  //        trar tempo entre pulsos ou contar   //
  //        eventos.                            //
  //                                            //
  // 4) Definir os ciclos de contagem real (RC) //
  //    até atingir o tempo desejado (TD) pelo  //
  //    usuário a partir da equação:            //
  //                                            //
  //                RD = FT x TD                //
  //                                            //
  //    Ex.:                                    //
  //       FT = 656.25kHz (para TIMER_CLOCK4)   //
  //       TD = 1 segundo (para o cronômetro)   //
  //       RD =  656.25kHz x 1s = 656250 ciclos //

  TC_Configure(TC0, 0,
               TC_CMR_TCCLKS_TIMER_CLOCK4 |  // FT = MCK/128 = 84MHz/128 = 656.25kHz
                 TC_CMR_WAVE |               // Modo wave
                 TC_CMR_WAVSEL_UP_RC);       // Contagem até RC

  TC_SetRC(TC0, 0, 656250);  // TD = 656250 ciclos / 656.25kHz = 1 segundo

  TC_Start(TC0, 0);
  TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;  // Habilita interrupção por comparação
                                            // (o bit de flag CPCS é setado quando
                                            // o estouro do timer for identificado)
  NVIC_EnableIRQ(TC0_IRQn);                 // Ativa a interrupção
}

// ROTINA DE INTERRUPÇÃO
void TC0_Handler() {
  TC_GetStatus(TC0, 0);  // Limpa o flag da interrupção
  atualizar = true;
}