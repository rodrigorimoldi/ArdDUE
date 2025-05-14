//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 8 - conversão D/A de sinais de tensão /
//                com 12 bits de resolução.
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: realizar a oscilografia dos 2 si-   /
//              nais analógicos gerados nas saídas  /
//              DAC0 (senoidal) e DAC1 (triangular) /
//              do Arduino DUE.                     /
//                                                  /
//**************************************************/

// ROTINA DE CONFIGURAÇÕES
void setup() {
    // Inicializa a comunicação serial
    Serial.begin(9600);

    // Habilita os canais DAC0 e DAC1
    analogWriteResolution(12); // Configura a resolução para 12 bits (0-4095)
}

// ROTINA PRINCIPAL
void loop() {
    // Teste: Gera um sinal de onda senoidal no DAC0 e uma onda triangular no DAC1

    for (int i = 0; i < 4096; i += 100) {
        int valorSenoide = (int)(2048 + 2048 * sin(i * PI / 2048)); // Onda senoidal
        int valorTriangular = (i < 2048) ? i : (4095 - i); // Onda triangular

        analogWrite(DAC0, valorSenoide);  // Escreve no DAC0
        analogWrite(DAC1, valorTriangular); // Escreve no DAC1

        Serial.print("DAC0: ");
        Serial.print(valorSenoide);
        Serial.print("\tDAC1: ");
        Serial.println(valorTriangular);

        //delay(10); // Pequeno atraso para suavizar a onda
    }
}