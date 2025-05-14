//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 9 - manipulação completa da Shield    /
//                Funduino Joystick
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: identificação das teclas A até F    /
//              como entradas digitais e também dos /
//              pinos correspondentes ao Joystick da/
//              Shield Funduino, para o qual tem-se /
//              a tecla KEY (Joy BTN) interpretada  /
//              como entrada digital e os 2 poten-  /
//              ciômetros dos eixos X e Y interpre- /
//              como entradas analógicas.           /
//                                                  /
//**************************************************/

// DEFINIÇÃO DE PARÂMETROS
#define JOY_X   A0  // Eixo X do joystick
#define JOY_Y   A1  // Eixo Y do joystick
#define JOY_BTN 8   // Botão do joystick

#define BTN_A   53  // Botão A (fio azul)
#define BTN_B   52  // Botão B (fio verde)
#define BTN_C   51  // Botão C (fio amarelo)
#define BTN_D   50  // Botão D (fio laranja)
#define BTN_E   49  // Botão E (fio vermelho)
#define BTN_F   48  // Botão F (fio marrom)

// ROTINA DE CONFIGURAÇÕES
void setup() {
  Serial.begin(115200);

  pinMode(BTN_A, INPUT);
  pinMode(BTN_B, INPUT);
  pinMode(BTN_C, INPUT);
  pinMode(BTN_D, INPUT);
  pinMode(BTN_E, INPUT);
  pinMode(BTN_F, INPUT);
}

void loop() {
    // Leitura dos valores analógicos do joystick
    int eixoX = analogRead(JOY_X);
    int eixoY = analogRead(JOY_Y);

    // Leitura dos botões (invertido, pois o pull-up mantém em HIGH)
    bool joyPressionado = digitalRead(JOY_BTN) == LOW;
    bool btnA = digitalRead(BTN_A) == LOW;
    bool btnB = digitalRead(BTN_B) == LOW;
    bool btnC = digitalRead(BTN_C) == LOW;
    bool btnD = digitalRead(BTN_D) == LOW;
    bool btnE = digitalRead(BTN_E) == LOW;
    bool btnF = digitalRead(BTN_F) == LOW;

    // Exibição dos valores no monitor serial
    Serial.print("Joystick X: ");
    Serial.print(eixoX);
    Serial.print(" | Joystick Y: ");
    Serial.print(eixoY);
    
    Serial.print(" | Joy BTN: ");
    Serial.print(joyPressionado ? "Pressionado" : "Solto");

    Serial.print(" | Botões: ");
    Serial.print(btnA ? "A " : "");
    Serial.print(btnB ? "B " : "");
    Serial.print(btnC ? "C " : "");
    Serial.print(btnD ? "D " : "");
    Serial.print(btnE ? "E " : "");
    Serial.print(btnF ? "F " : "");

    Serial.println();  // Nova linha

    delay(200);  // Pequena pausa para evitar spam no monitor serial
}
