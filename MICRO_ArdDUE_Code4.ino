//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 4 - varredura de teclado matricial    /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: identificação das teclas pressiona- /
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
#define lin1    44  // Pino 44
#define lin2    45  // Pino 45
#define lin3    46  // Pino 46
#define lin4    47  // Pino 47
#define col1    40  // Pino 40
#define col2    41  // Pino 41
#define col3    42  // Pino 42
#define col4    43  // Pino 43
#define nroLin  4   // Número de linhas
#define nroCol  4   // Número de colunas

// DECLARAÇÃO DE VARIÁVEIS GLOBAIS
uint lin, col;

// MAPEAMENTO DAS TECLAS
char tecla[nroLin][nroCol] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// ROTINA DE CONFIGURAÇÕES
void setup() {
  pinMode(lin1, INPUT);  // Linhas como entradas
  pinMode(lin2, INPUT);
  pinMode(lin3, INPUT);
  pinMode(lin4, INPUT);
  pinMode(col1, OUTPUT);  // Colunas como saídas
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT);
  pinMode(col4, OUTPUT);

  digitalWrite(col1, HIGH);  // Escrita inicial pré varredura
  digitalWrite(col2, HIGH);
  digitalWrite(col3, HIGH);
  digitalWrite(col4, HIGH);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("TEC. MATRICIAL");
  lcd.setCursor(0, 1);
  lcd.print("Tecla: ");
}

// ROTINA PRINCIPAL
void loop() {
  // Varredura das colunas
  for (col = 40; col <= 43; col++) {
    digitalWrite(col, LOW);  // A coluna lida é colocada em 0

    // Leitura das linhas e escrita de resultado
    for (lin = 44; lin <= 47; lin++) {
      lcd.setCursor(7, 1);
      lcd.write(0xFE);

      if (!digitalRead(lin)) {
        lcd.setCursor(7, 1);
        lcd.write(tecla[(lin - 44)][(col - 40)]);
        while (!digitalRead(lin)) {}
      }
    }
    digitalWrite(col, HIGH);  // Restauração da coluna para 1
  }
}