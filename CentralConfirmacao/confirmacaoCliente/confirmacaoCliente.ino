//=========================================
//= Desenvolvido por : Ronan Nunes Campos =
//=                                       =
//=                                       =
//= Trabalho Embarcados                   =
//= ComeQueTaBao                          =
//=========================================

#include <ESP8266WiFi.h>
#include <RCSwitch.h>
String refresh = "";
String req;
String buf;
//String recebido = "";
String className1 = "";
String className2 = "";
String className3 = "";

String valueName1 = "Pedir Confirmação Mesa 1";
String valueName2 = "Pedir Confirmação Mesa 2";
String valueName3 = "Pedir Confirmação Mesa 3";

const char* ssid = "CASA 247";    //nome da sua rede
const char* password = "#trend@247!fskd"; //senha da sua rede

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

// variavel usado para receber o dado transmitido
int dadoRecebido = 0;

RCSwitch mySwitchTrans = RCSwitch();
RCSwitch mySwitchReceiv = RCSwitch();

//IP do roteador da sua rede wifi
IPAddress gateway(198, 162, 0, 1);

//Mascara de rede da sua rede wifi
IPAddress subnet(255, 255, 255, 0);

//Criando o servidor web na porta 80
WiFiServer server(80);

//Pino do NodeMCU que estara conectado ao transmissor
const int pinRF = 14; //Equivalente ao D5 no NodeMCU

//Funcao que sera executada apenas ao ligar o ESP8266
void setup() {

  Serial.begin(9600);

  mySwitchTrans.enableTransmit(pinRF);
  delay(500);
  
  //pino equivalente D8
  mySwitchReceiv.enableReceive(0);
  delay(500);
  
  //Conectando a rede Wifi
  //WiFi.config();
  WiFi.begin(ssid, password);

  Serial.print("Conectando... ");
  //Verificando se esta conectado,
  //caso contrario, espera um pouco e verifica de novo.
  while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
    Serial.print(".");
  }
  
  //Iniciando o servidor Web
  server.begin();
  
  Serial.print("Servidor startado em ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  Serial.println("Conectado :)"); 
}

//Funcao que sera executada indefinidamente enquanto o WEMOS estiver ligado.
void loop() {
  
  WiFiClient client = server.available();
  
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("desconectou :(");
    Serial.print("Conectando...");
    
    //Verificando se esta conectado,
    //caso contrario, espera um pouco e verifica de novo.
    while (WiFi.status() != WL_CONNECTED) {
      
      delay(500);
      Serial.print(".");
    }  
    Serial.println("Conectado :)");
  }   

  //Quado estiver sinal disponivel
  if (mySwitchReceiv.available()) {

    //Valor recebe a mensagem
    dadoRecebido = mySwitchReceiv.getReceivedValue();

      if (dadoRecebido == protocoloMesa1EnviaConfirmar){

         className1 = "list-group-item-success";
         valueName1 = "Pedido Confirmado: Mesa 1";
         refresh = "";
         delay(500);
         
         mySwitchTrans.send(protocoloMesa1PedidoConfirmado, 24);
         delay(500);
           
      }else if(dadoRecebido == protocoloMesa1EnviaCancelar){

         className1 = "list-group-item-danger";
         valueName1 = "Pedido Cancelado: Mesa 1";
         refresh = "";
         delay(500);
         
         mySwitchTrans.send(protocoloMesa1PedidoCancelado, 24);
         delay(500);    
      }      
    
    criaPagina();
  
    //Enviando para o browser a 'pagina' criada.
    client.print(buf);
    delay(1000);
    mySwitchReceiv.resetAvailable();       
  }
  
  //Verificando se o servidor esta pronto.
  
  if (!client) {
    
    return;
  }

  //Verificando se o servidor recebeu alguma requisicao
  while (!client.available()) {

    delay(10);
  }

  //Obtendo a requisicao vinda do browser
  req = client.readStringUntil('\r');

  //Sugestao dada por Enrico Orlando
  if (req == "GET /favicon.ico HTTP/1.1") {
    
    req = client.readStringUntil('\r');
  }

  client.flush();
  
  //Analisando a requisicao recebida
  
  if (req.indexOf("Mesa1") != -1){

    mySwitchTrans.send(protocoloMesa1PedeConfirmacao, 24);
    delay(500);
   
    
    refresh = "<meta http-equiv='refresh' content='2; http://192.168.0.109'>"; 
    
    className1 = "list-group-item-warning";
    valueName1 = "Aguardando Confirmação Mesa 1"; 
    
    Serial.println("pediu confirmação para mesa 1");   
    delay(500);         
  
  }else if (req.indexOf("Mesa2") != -1){

    refresh = "<meta http-equiv='refresh' content='2; http://192.168.0.109'>";
    
    className2 = "list-group-item-warning";
    valueName2 = "Aguardando Confirmação Mesa 2";
    
    Serial.println("pediu confirmação para mesa 2");
    delay(500);  
  
  }else if (req.indexOf("Mesa3") != -1){

    refresh = "<meta http-equiv='refresh' content='2; http://192.168.0.109'>";
    
    className3 = "list-group-item-warning";
    valueName3 = "Aguardando Confirmação Mesa 3";
    
    Serial.println("pediu confirmação para mesa 3");
    delay(500);    
  }

  criaPagina();
  
  //Enviando para o browser a 'pagina' criada.
  client.print(buf); 

}

void criaPagina(){

    //Iniciando o buffer que ira conter a pagina HTML que sera enviada para o browser.
  buf = "";
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html lang='en'>\r\n";
  buf += "<head>";
  buf += refresh;
  buf += "<meta charset='utf-8'>";
  buf += "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>";
  buf += "<meta http-equiv='x-ua-compatible' content='ie=edge'>";
  buf += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>";
  buf += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.4/css/bootstrap.min.css' integrity='2hfp1SzUoho7/TsGGGDaFdsuuDL0LX2hnUp6VkX3CUQ2K4K+xjboZdsXyp4oUHZj' crossorigin='anonymous'>";
  buf += "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>";
  buf += "<script src='https://cdnjs.cloudflare.com/ajax/libs/tether/1.2.0/js/tether.min.js' integrity='sha384-Plbmg8JY28KFelvJVai01l8WyZzrYWG825m+cZ0eDDS1f7d/js6ikvy1+X+guPIB' crossorigin='anonymous'></script>";
  buf += "<script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.4/js/bootstrap.min.js' integrity='VjEeINv9OSwtWFLAtmc4JCtEJXXBub00gtSnszmspDLCtC0I4z4nqz7rEFbIZLLU' crossorigin='anonymous'></script>";
  buf += "<title>ComeQueTaBao</title>";
  buf += "</head>"; 
  
  buf += "<body> ";
 
  buf += "<nav class='navbar navbar-fixed-top navbar-dark bg-inverse bg-faded'>";
  buf +="<font class='lead'>Auto Atendimento</font>";        
  buf += "</nav>";
  
  buf += "<div class='container-fluid'>";
  buf += "<div class='row'>";
  
  buf += "<div class='col-lg-2 col-md-2 col-sm-12'></div>";
  
  buf += "<div class='col-lg-8 col-md-8 col-sm-12'>";   
  
  buf += "<br><br><br>";
  
  buf += "<div class='list-group'>";
  
  buf += "<a class='list-group-item "+className1+"' href='?f=Mesa1' role='button'>"+valueName1+"</a>";
  buf += "<a class='list-group-item "+className2+"' href='?f=Mesa2' role='button'>"+valueName2+"</a>";
  buf += "<a class='list-group-item "+className3+"' href='?f=Mesa3' role='button'>"+valueName3+"</a>";                  
 
  buf += "</div>";   
  
  buf += "<br><br><br>";               
  
  buf += "</div>";
 
  buf += "<div class='col-lg-2 col-md-2 col-sm-12'></div>";
  
  buf += "</div>";  
  buf += "</div>"; 
  
  buf += "<nav class='navbar navbar-fixed-bottom bg-faded'>";
  buf += "<p class='lead' align='center'>ComeQueTaBao</p>";
  
  buf += "</nav>";
  buf += "</body>";
  buf += "</html>";
  
}
