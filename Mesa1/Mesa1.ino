#include <RCSwitch.h>
#include "LCD5110_Basic.h"

LCD5110 tela(8,9,10,12,11);

// CLK – Pino 8

// DIN – Pino 9

// DC – Pino 10

// RST – Pino 12

// CE – Pino 11

//Protocolo Mesa 1
//Pede confirmação
const int protocoloMesa1PedeConfirmacao = 111;
//Confirma pedido
const int protocoloMesa1PedidoConfirmado = 110;
//Pedido Cancelado
const int protocoloMesa1PedidoCancelado = 1110;
//Envia confirmação
const int protocoloMesa1EnviaConfirmar = 1100;
//Envia cancela
const int protocoloMesa1EnviaCancelar = 1011;

extern uint8_t SmallFont[];

int confirmar = 3;
int cancelar = 4;

int leituraBotaoConfirma;
int leituraBotaoCancela;

// variavel usado para receber o dado transmitido
int dadoRecebido = 0;

//Pino do Arduino que estara conectado ao transmissor
const int pinRF = 13;

RCSwitch mySwitchTrans = RCSwitch();
RCSwitch mySwitchReceiv = RCSwitch();

void setup() {
  
  //inicia o monitor serial na valocidade 9600
  Serial.begin(9600);

  // delay para estabilizacao do Sinal
  delay(500);

  tela.InitLCD();

  delay(500);

  mySwitchTrans.enableTransmit(pinRF);
  delay(500);

  pinMode(confirmar, INPUT);
  pinMode(cancelar, INPUT);
 
  //Seta como Receptor O "0" é para não interromper, deixar continuo
  //O Pino padrão é o 2
  mySwitchReceiv.enableReceive(0); 
  delay(500);

  delay(2000);
  tela.clrScr();
  tela.setFont(SmallFont);
  tela.print("Bem Vindo", LEFT, 0); 
  tela.print("Mesa 1", LEFT, 8); 
  
}

void loop() {
  
  leituraBotaoConfirma = digitalRead(confirmar); 
  leituraBotaoCancela = digitalRead(cancelar); 

  if(leituraBotaoConfirma != 0){

    while(digitalRead(confirmar) != 0){
      delay(100);
    }

    tela.clrScr();
    tela.setFont(SmallFont);
    tela.print("Confirmar", LEFT, 0);
    tela.print("Pedido", LEFT, 8);
    
    mySwitchTrans.send(protocoloMesa1EnviaConfirmar, 24);
    delay(500);
  }

  if(leituraBotaoCancela != 0){

    while(digitalRead(cancelar) != 0){
      delay(100);
    }

    tela.clrScr();
    tela.setFont(SmallFont);
    tela.print("Cancelar", LEFT, 0);
    tela.print("Pedido", LEFT, 8);
    
    mySwitchTrans.send(protocoloMesa1EnviaCancelar, 24);
    delay(500);
  }

  //Quado estiver sinal disponivel
  if (mySwitchReceiv.available()) {

    dadoRecebido = mySwitchReceiv.getReceivedValue();

      if (dadoRecebido == protocoloMesa1PedeConfirmacao){    
        
        tela.clrScr();
        tela.setFont(SmallFont);
        tela.print("Por favor,", LEFT, 0);
        tela.print("Confirme ou", LEFT, 8);
        tela.print("Cancele", LEFT, 16);
        tela.print("seu pedido", LEFT, 24);
        tela.print(dadoRecebido, LEFT, 32);

      }else if (dadoRecebido == protocoloMesa1PedidoCancelado){

        tela.clrScr();
        tela.setFont(SmallFont);
        tela.print("Pedido", LEFT, 0);
        tela.print("Cancelado", LEFT, 8);

      }else if (dadoRecebido == protocoloMesa1PedidoConfirmado){

        tela.clrScr();
        tela.setFont(SmallFont);
        tela.print("Pedido", LEFT, 0);
        tela.print("Confirmado", LEFT, 8);
        
      }
      
    mySwitchReceiv.resetAvailable();       
  }  
}
