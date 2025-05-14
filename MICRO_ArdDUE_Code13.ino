// Gera PWM no pino 6 do Arduino DUE (PWML7 = PC23)

void setup() {
  // Habilita o clock do periférico PWM
  pmc_enable_periph_clk(PWM_INTERFACE_ID);

  // Desativa o PWM para configurar
  PWM->PWM_DIS = PWM_DIS_CHID7;

  // Configura o pino 6 como saída PWM (PWML7 - PC23)
  PIOC->PIO_PDR |= PIO_PDR_P23;  // Desabilita controle do PIO
  PIOC->PIO_ABSR |= PIO_PC23B_PWMH7; // Conecta ao periférico B (PWM)

  // Configura o clock do PWM: PWM_CLK = MCK / divisor
  PWM->PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(42); 
  // Clock PWM = 84 MHz / 42 = 2 MHz

  // Configura o canal 7: modo PWM, alinhamento à esquerda, polaridade padrão
  PWM->PWM_CH_NUM[7].PWM_CMR = PWM_CMR_CPRE_CLKA;

  // Define período e duty cycle
  PWM->PWM_CH_NUM[7].PWM_CPRD = 2000;   // Período = 2000 ticks -> 1 kHz
  PWM->PWM_CH_NUM[7].PWM_CDTY = 1000;   // Duty = 1000 ticks -> 50%

  // Habilita o canal 7
  PWM->PWM_ENA = PWM_ENA_CHID7;
}

void loop() {
  // Exemplo: aumentar gradualmente o duty cycle para controlar a velocidade
  for (int duty = 0; duty <= 2000; duty += 100) {
    PWM->PWM_CH_NUM[7].PWM_CDTYUPD = duty; // Atualiza duty cycle
    delay(100);
  }

  delay(1000);

  // Exemplo: diminuir gradualmente
  for (int duty = 2000; duty >= 0; duty -= 100) {
    PWM->PWM_CH_NUM[7].PWM_CDTYUPD = duty;
    delay(100);
  }

  delay(1000);
}
