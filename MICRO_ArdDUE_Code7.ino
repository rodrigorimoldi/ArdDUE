//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 7 - conversão A/D de sinais de tensão /
//                com 12 bits de resolução.
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: tratamento de sinais analógicos em- /
//              pregando os recursos mencionados no /
//              capítulo 43 do datasheet do proces- /
//              sador ARM Cortex-M3 RISC da Atmel,  /
//              série SAM3X8E de 32 bits, empregado /
//              na placa de desenvolvimento do Ar-  /
//              duino DUE.                          /
//                                                  /
//**************************************************/

// DEFINIÇÃO DE PARÂMETROS
#define potenciometro A0  // Define o pino analógico A0 para leitura do potenciômetro

// ROTINA DE CONFIGURAÇÕES
void setup() {
    Serial.begin(115200);     // Inicializa a comunicação serial
    analogReadResolution(12); // Configura a resolução do ADC para 12 bits (0 a 4095)
                              // (recurso disponível apenas para Arduino DUE e ESP32)
}

// ROTINA PRINCIPAL
void loop() {
    int valorADC = analogRead(potenciometro); // Lê o valor do ADC (0 a 4095)
    float tensao = valorADC * (3.4 / 4095.0); // Converte para tensão (0 a 5V)
                                              // OBS.: Sempre convém aferir o 
                                              //       FE com um multímetro ou
                                              //       osciloscópio para melho-
                                              //       rar a leitura de dados.
    
    Serial.print("Valor ADC: ");
    Serial.print(valorADC);
    Serial.print(" - Tensao: ");
    Serial.print(tensao);
    Serial.println(" V");

    delay(250);  // Aguarda 250 ms antes da próxima leitura
}
