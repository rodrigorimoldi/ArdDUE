//**************************************************/
//    UFTM  |  DEE  |  MICROCONTROLADORES           /
//    PROF. DR. RODRIGO RIMOLDI DE LIMA             /
//                                                  /
// ------------------------------------------------ /
//    PRÁTICA 5 - operações com display gráfico LCD /
//                128x64 sem recurso touchscreen    /
// ------------------------------------------------ /
//                                                  /
//    OBJETIVO: exibição de mensagens utilizando    /
//              diferentes fontes e tamanhos, exi-  /
//              bição de caracteres da tabela ASCii,/
//              manipulação de formas geométricas e /
//              exibição de imagens complexas con-  /
//              vertidas em byte arrays.            /
//                                                  /
//**************************************************/

// INCLUSÃO DE BIBLIOTECAS
#include "U8glib.h"
// Maiores informações em:
// https://github.com/olikraus/u8glib/wiki/userreference?tab=readme-ov-file#user-reference-manual


// DEFINIÇÃO DA PINAGEM DO DISPLAY GRÁFICO LCD 128x64
// u8g2(U8G2_R0, E, R/W, D/I, RST)
U8GLIB_ST7920_128X64_1X u8g(39, 38, 37, 36);
int display = 1;

// PREPARAÇÃO INICIAL
void u8g_prepare() {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

//TELA 1 - UFTM e retângulos
void u8g_Tela1() {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(22, 35, "UFTM - DEE");
  u8g.drawStr(23, 35, "UFTM - DEE");
  u8g.drawFrame(0, 0, 128, 64);
  u8g.drawFrame(2, 2, 124, 60);
}

//TELA 2 - Moldura e relógio
void u8g_Tela2() {
  u8g.drawRFrame(0, 0, 128, 64, 3);
  u8g.drawStr(3, 10, "Hor.: 13:00");
  u8g.drawStr(3, 25, "Temp: 27");
  char s[2] = " ";
  s[1] = 176;
  u8g.drawStr(51, 25, s);
  u8g.drawStr(3, 40, "Umid: 25%");
  u8g.drawCircle(95, 32, 28);
  u8g.drawCircle(95, 32, 29);
  u8g.drawLine(95, 9, 95, 4);
  u8g.drawLine(123, 32, 118, 32);
  u8g.drawLine(95, 55, 95, 60);
  u8g.drawLine(67, 32, 72, 32);
  u8g.drawLine(95, 32, 95, 12);
  u8g.drawLine(95, 32, 100.8, 21.87);
  u8g.setFont(u8g_font_04b_03);
  u8g.drawStr(89, 43, "Tag");
  u8g.drawStr(85, 50, "Heuer");
}

//TELA 3 - Caracteres Ascii - Pag. 1
void u8g_Tela3() {
  char s[2] = " ";
  u8g.drawStr(0, 0, "ASCII p. 1");
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 16; x++) {
      s[0] = y * 16 + x + 32;
      u8g.drawStr(x * 7, y * 10 + 10, s);
    }
  }
}

//TELA 3 - Caracteres Ascii - Pag. 2
void u8g_Tela4() {
  char s[2] = " ";
  uint8_t x, y;
  u8g.drawStr(0, 0, "ASCII p. 2");
  for (y = 0; y < 6; y++) {
    for (x = 0; x < 16; x++) {
      s[0] = y * 16 + x + 160;
      u8g.drawStr(x * 7, y * 10 + 10, s);
    }
  }
}

//TELA 5 - Microcontroladores e retângulo preenchido
void u8g_Tela5() {
  u8g.setFont(u8g_font_unifont);
  u8g.drawBox(0, 0, 128, 64);
  u8g.drawBox(2, 2, 124, 60);
  u8g.setColorIndex(0);
  u8g.drawStr(21, 35, "MICRO 2025");
  u8g.drawStr(22, 35, "MICRO 2025");
  u8g.drawFrame(2, 2, 124, 60);
}

//TELA 6 - Prof. Rodrigo Rimoldi em 0, 90 e 270 graus
void u8g_Tela6() {
  u8g.setFont(u8g_font_courR08);
  u8g.drawStr(50, 31, " Rodrigo");
  u8g.drawStr90(50, 31, " Prof.");
  u8g.drawStr270(50, 51, " Rimoldi");
}

//TELA 7 - Fontes diferentes
void u8g_Tela7() {
  u8g.setFont(u8g_font_robot_de_niro);
  u8g.drawStr(5, 13, "Arduino DUE");
  u8g.setFont(u8g_font_helvB08);
  u8g.drawStr(5, 25, "Arduino DUE");
  u8g.drawBox(5, 31, 118, 11);
  u8g.setColorIndex(0);
  u8g.setFont(u8g_font_8x13);
  u8g.drawStr(5, 41, "Arduino DUE");
  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_ncenB10);
  u8g.drawStr(5, 60, "Arduino DUE");
}

//TELA 8 - Figuras geométricas
void u8g_Tela8() {
  u8g.drawEllipse(100, 35, 25, 10, U8G_DRAW_ALL);
}

// ROTINA DE DESENHO
void draw() {
  u8g_prepare();
  switch (display)  //Carrega a tela correspondente
  {
    case 1:
      u8g_Tela1();
      break;
    case 2:
      u8g_Tela2();
      break;
    case 3:
      u8g_Tela3();
      break;
    case 4:
      u8g_Tela4();
      break;
    case 5:
      u8g_Tela5();
      break;
    case 6:
      u8g_Tela6();
      break;
    case 7:
      u8g_Tela7();
      break;
    case 8:
      u8g_Tela8();
      break;
  }
}

// ROTINA DE CONFIGURAÇÕES
void setup() {
  // flip screen, if required
  //u8g.setRot180();

  // assign default color value
  if (u8g.getMode() == U8G_MODE_R3G3B2)
    u8g.setColorIndex(255);  // white
  else if (u8g.getMode() == U8G_MODE_GRAY2BIT)
    u8g.setColorIndex(1);  // max intensity
  else if (u8g.getMode() == U8G_MODE_BW)
    u8g.setColorIndex(1);  // pixel on

  u8g.setContrast(0x30);
}

// ROTINA PRINCIPAL
void loop() {
  // picture loop
  for (display = 1; display <= 8; display++)  //Carrega as telas de 1 a 7
  {
    u8g.firstPage();
    do {
      draw();
    } while (u8g.nextPage());
    delay(3000);  //Pausa de 3 segundos e reinicia o processo
  }
}