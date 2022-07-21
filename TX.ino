/* Blog Eletrogate - Monitor de Nível de Caixa Dagua - Transmissor
   Gustavo Murta 14/ago/2019
   Arduino UNO - IDE 1.8.9
   pino D12 - transmite dados
   https://github.com/sui77/rc-switch/
*/

#include <RCSwitch.h>                   // biblioteca RCSwitch V 2.62

RCSwitch transmissor = RCSwitch();      // cria a instancia transmissor 

int sensor_100 = 7;                     // chave boia 100% - pino D7
int sensor_75 = 6;                      // chave boia 75%  - pino D6
int sensor_50 = 5;                      // chave boia 50%  - pino D5
int sensor_25 = 4;                      // chave boia 25%  - pino D4

int led_100 = 11;                       // Led 100% - pino D11
int led_75 = 10;                        // Led 75%  - pino D10
int led_50 = 9;                         // Led 50%  - pino D9
int led_25 = 8;                         // Led 25%  - pino D8

int nivel_100;                          // variáveis de niveis 
int nivel_75;
int nivel_50;
int nivel_25;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);                             // led D13 integrado na placa
  pinMode(led_100, OUTPUT); pinMode(led_75, OUTPUT);        // configurações das portas dos Leds 
  pinMode(led_50, OUTPUT); pinMode(led_25, OUTPUT);
  pinMode(sensor_100, INPUT); pinMode(sensor_75, INPUT);    // configurações das portas dos sensores
  pinMode(sensor_50, INPUT); pinMode(sensor_25, INPUT);

  transmissor.enableTransmit(12);                           // pino usado para transmissão
  transmissor.setPulseLength(500);                          // largura do pulso em microseg
  transmissor.setProtocol(6);                               // protocolo de trasmissão
  transmissor.setRepeatTransmit(16);                        // numero de repetidas transmissões
}

void loop()
{
  digitalWrite(LED_BUILTIN,HIGH);             // acende Led do Arduino
  
  nivel_100 = digitalRead(sensor_100);        // leitura do sensor 100%
  digitalWrite(led_100,nivel_100);
  
  nivel_75 = digitalRead(sensor_75);          // leitura do sensor 75%
  digitalWrite(led_75,nivel_75);
  
  nivel_50 = digitalRead(sensor_50);          // leitura do sensor 50%
  digitalWrite(led_50,nivel_50);
  
  nivel_25 = digitalRead(sensor_25);          // leitura do sensor 25%
  digitalWrite(led_25,nivel_25);
  

  if ((nivel_100 == HIGH) && (nivel_75 == HIGH) && (nivel_50 == HIGH) && (nivel_25 == HIGH))
  {   
    transmissor.send(1285, 24);               // caixa dagua vazia
  }
  if ((nivel_100 == HIGH) && (nivel_75 == HIGH) && (nivel_50 == HIGH) && (nivel_25 == LOW))
  {
       transmissor.send(1301, 24);             // caixa dagua 25%
  }
  if ((nivel_100 == HIGH) && (nivel_75 == HIGH) && (nivel_50 == LOW) && (nivel_25 == LOW))
  {
       transmissor.send(1333, 24);             // caixa dagua 50%
  }
  if ((nivel_100 == HIGH) && (nivel_75 == LOW) && (nivel_50 == LOW) && (nivel_25 == LOW))
  {
      transmissor.send(1397, 24);              // caixa dagua 75%
  }
  if ((nivel_100 == LOW) && (nivel_75 == LOW) && (nivel_50 == LOW) && (nivel_25 == LOW))
  {
        transmissor.send(1525, 24);            // caixa dagua 100% cheia
  }
  digitalWrite(LED_BUILTIN,LOW);               // apaga Led do Arduino
  delay(2000);                                 // pausa de 2 segundos
}