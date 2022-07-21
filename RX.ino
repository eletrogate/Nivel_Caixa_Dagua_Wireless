/* Blog Eletrogate - Monitor de Nível de Caixa Dagua - Receptor + display Oled
   Gustavo Murta 14/ago/2019
   Arduino UNO - IDE 1.8.9
   pino D2 - receptor de dados
   https://github.com/sui77/rc-switch/
   https://github.com/adafruit/Adafruit_SSD1306
   https://github.com/adafruit/Adafruit-GFX-Library
   OLED I2C   SDA = A4 e SCL = A5
   drawRoundRect(x,y,w,h,r,color)
   x   coordenada x (topo esquerda)
   y   coordenada y (topo esquerda)
   w   largura em pixels
   h   altura em pixels
   r   raio da borda
   color  cor
*/

//#include <Wire.h>                                   // biblioteca I2C
#include <Adafruit_GFX.h>                            // biblioteca gráfica da Adafruit
#include <Adafruit_SSD1306.h>                        // biblioteca Oled da Adafruit
#include <Fonts/FreeMono9pt7b.h>                     // tipo de fonte do caracter
#include <RCSwitch.h>                                // biblioteca RCswitch V 2.6.2

RCSwitch receptor = RCSwitch();

#define SCREEN_WIDTH 128                             // largura do display 128 pixels
#define SCREEN_HEIGHT 64                             // altura do display 64 pixels 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int valor;
unsigned long inicialTimer = 0;
unsigned long finalTimer;
boolean falha = false;

void setup()
{  
  pinMode(13, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();                                              // limpa o display
  display.setFont(&FreeMono9pt7b);                                     // tipo de fonte
  display.setTextSize(1);                                              // tamamho do caracter
  displayMessage ();                                                   // mostra mensagem no display
  caixa25(false);  caixa50(false);  caixa75(false);  caixa100(false);  // caixa vazia
  receptor.enableReceive(0);                                           // ativa Recepção - pino do receptor = D2 Arduino
}

void caixa25(boolean cheia)
{
  if (cheia == true)
  {
    display.fillRoundRect(0, 0, 30, 40, 2, WHITE);    // preencha o retangulo
    display.setTextColor(BLACK);
  }
  else
  {
    display.fillRoundRect(0, 0, 30, 40, 2, BLACK);    // apague o retangulo
    display.drawRoundRect(0, 0, 30, 40, 2, WHITE);    // desenhe o retangulo
    display.setTextColor(WHITE);
  }
  display.setCursor(4, 25);
  display.println("25");
  display.display();
}

void caixa50(boolean cheia)
{
  if (cheia == true)
  {
    display.fillRoundRect(31, 0, 30, 40, 2, WHITE);    // preencha o retangulo
    display.setTextColor(BLACK);
  }
  else
  {
    display.fillRoundRect(31, 0, 30, 40, 2, BLACK);   // apague o retangulo
    display.drawRoundRect(31, 0, 30, 40, 2, WHITE);   // desenhe o retangulo
    display.setTextColor(WHITE);
  }
  display.setCursor(35, 25);
  display.println("50");
  display.display();
}

void caixa75(boolean cheia)
{
  if (cheia == true)
  {
    display.fillRoundRect(62, 0, 30, 40, 2, WHITE);    // preencha o retangulo
    display.setTextColor(BLACK);
  }
  else
  {
    display.fillRoundRect(62, 0, 30, 40, 2, BLACK);   // apague o retangulo
    display.drawRoundRect(62, 0, 30, 40, 2, WHITE);   // desenhe o retangulo
    display.setTextColor(WHITE);
  }
  display.setCursor(66, 25);
  display.println("75");
  display.display();
}

void caixa100(boolean cheia)
{
  if (cheia == true)                                   // se caixa 100 estiver cheia
  {
    display.fillRoundRect(93, 0, 31, 40, 2, WHITE);    // preencha o retangulo cor branca
    display.setTextColor(BLACK);                       // selecione cor preta
  }
  else                                                 // senão
  {
    display.fillRoundRect(93, 0, 31, 40, 2, BLACK);    // apague o retangulo
    display.drawRoundRect(93, 0, 31, 40, 2, WHITE);    // desenhe o retangulo cor branca
    display.setTextColor(WHITE);                       // selecione cor branca
  }
  display.setCursor(91, 25);                           // coordenadas x e y
  display.println("100");                              // escreva 100
  display.display();                                   // mostra no display
}

void displayMessage ()
{
  display.setTextColor(WHITE);           // selecione cor branca
  display.setCursor(2, 60);              // coordenadas x e y
  display.println("CAIXA DAGUA");        // escreve mensagem
  display.display();                     // mostra no display
}

void displayFalha ()
{  
  display.fillRoundRect(0, 0, 127, 40, 1, BLACK);    // apague o retangulo
  display.setTextColor(WHITE);                       // selecione cor branca
  display.setCursor(30, 10);                         // coordenadas x e y
  display.println("FALHA");                          // escreve mensagem
  display.setCursor(20, 30);                         // coordenadas x e y
  display.println("DE SINAL");                       // escreve mensagem
  display.display();                                 // mostra no display
}

void loop()
{
  valor = 0;
  finalTimer = millis();
  if (receptor.available())
  {
    valor = receptor.getReceivedValue();
    receptor.resetAvailable();
    inicialTimer = millis();   
  }
  if (finalTimer - inicialTimer >= 4000)
  {
    displayFalha ();
    inicialTimer = finalTimer;
  }
  if (valor == 1285)                               // caixa dagua vazia
  {
    digitalWrite(13, HIGH);
    caixa25(false);  caixa50(false);  caixa75(false);  caixa100(false);
    digitalWrite(13, LOW);
  }
  if (valor == 1301)                               // caixa dagua 25%
  {
    digitalWrite(13, HIGH);
    caixa25(true);  caixa50(false);  caixa75(false);  caixa100(false);
    digitalWrite(13, LOW);
  }
  if (valor == 1333)                               // caixa dagua 50%
  {
    digitalWrite(13, HIGH);
    caixa25(true);  caixa50(true);  caixa75(false);  caixa100(false);
    digitalWrite(13, LOW);
  }
  if (valor == 1397)                               // caixa dagua 75%
  {
    digitalWrite(13, HIGH);
    caixa25(true);  caixa50(true);  caixa75(true);  caixa100(false);
    digitalWrite(13, LOW);
  }
  if (valor == 1525)                               // caixa dagua 100% cheia
  {
    digitalWrite(13, HIGH);
    caixa25(true);  caixa50(true);  caixa75(true);  caixa100(true);
    digitalWrite(13, LOW);
  }
}