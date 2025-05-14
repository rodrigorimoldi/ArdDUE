//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 2 - operações com o display LCD 16x2  /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: escrita de mensagens na tela do     /
//              display LCD 16x2, manipulando os    /
//              recursos disponíveis na biblioteca  /
//              LiquidCrystal.h, padrão da plata-   /
//              forma Arduino IDE.                  /
//                                                  /
//**************************************************/

// INCLUSÃO DE BIBLIOTECAS
#include <LiquidCrystal.h>

// DEFINIÇÃO DA PINAGEM DO DISPLAY LCD 16x2
LiquidCrystal lcd(7, 6, 2, 3, 4, 5);  // (RS, E, D4, D5, D6, D7)

// DEFINIÇÃO DE PARÂMETROS
#define TIME 5000             // Aguarda 5 segundos

// DEFINIÇÃO DE VARIÁVEIS GLOBAIS
unsigned int i;

// CRIAÇÃO DE NOVOS CARACTERES
// OBS.: A memória EEPROM interna suporta até 8 novos.
byte smile1[8] = {  // Primeiro novo caracter criado
  B00000,
  B10001,
  B10001,
  B00000,
  B10001,
  B01110,
  B00000,
};

byte smile2[8] = {  // Primeiro novo caracter criado
  B00000,
  B10000,
  B10011,
  B00000,
  B10001,
  B01110,
  B00000,
};

// ROTINA DE CONFIGURAÇÕES
void setup() {
  lcd.begin(16, 2);           // Inicializa o LCD no modo 16x2
  lcd.createChar(0, smile1);  // Alocação do caracter na posição 0x40
  lcd.createChar(1, smile2);  // Alocação do caracter na posição 0x40
}

// ROTINA PRINCIPAL
void loop() {
  lcd.clear();                // Limpa por completo a tela do display
  lcd.noCursor();             // Oculta a base do cursor na tela do display
  lcd.blink();                // Exibe o cursor completo piscando
  lcd.setCursor(0, 0);        // Posiciona escrita na coluna 1 e linha 1
  lcd.print("UFTM  -  DEE");  // Texto da linha 1
  lcd.setCursor(0, 1);        // Posiciona escrita na coluna 2 e linha 1
  lcd.print("MICRO 2025.1");  // Texto da linha 2
  delay(TIME);

  lcd.noDisplay();            // Apaga o conteúdo da tela do display
  delay(TIME / 5);            // Fração de tempo ajustada
  lcd.display();              // Restaura o conteúdo da tela do display

  lcd.setCursor(0, 0);
  lcd.print("UFTM  -  DEE");
  lcd.setCursor(0, 1);
  lcd.print("MICRO 2025.1");
  delay(TIME / 2);

  for (i = 0; i < 16; i++) {  // Ação aplicada em 16 posições (colunas)
    lcd.scrollDisplayLeft();  // Rola o conteúdo da tela 1 espaço à esquerda
    delay(150);               // Intrevalo de 250 ms para cada rolagem
  }

  lcd.clear();
  lcd.cursor();   // Exibe a base do cursor na tela do display
  lcd.noBlink();  // Oculta o cursor completo piscando
  lcd.setCursor(0, 0);
  lcd.print("PROF. RIMOLDI");
  lcd.setCursor(0, 1);
  lcd.print("ARDUINO DUE");
  delay(TIME);

  for (i = 0; i < 16; i++) {  // Ação aplicada em 16 posições (colunas)
    lcd.scrollDisplayRight(); // Rola o conteúdo da tela 1 espaço à direita
    delay(150);               // Intrevalo de 250 ms para cada rolagem
  }

  lcd.clear();
  lcd.noCursor();
  lcd.noBlink();
  lcd.setCursor(0, 0);
  lcd.print("PROF. RIMOLDI");
  lcd.setCursor(0, 1);
  lcd.write(byte(0));         // Exibição do novo caracter 1
  delay(TIME / 7);
  lcd.setCursor(0, 1);
  lcd.write(byte(1));         // Exibição do novo caracter 1
  delay(TIME / 5);
  lcd.write(0xE2);         // Exibição de caracter da tabela ASCii (beta)
  delay(TIME);
}
