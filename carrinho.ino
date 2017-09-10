#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial NteSerial(6,7); // Rx, Tx 

 /* MÓDULO DRIVER COM DUPLA PONTE-H - L298 + MOTOR DC:
   liga-se os pinos ENA, IN1, IN2, IN3, IN4 e ENB do módulo nas 
   portas digitais D8, D9, D10 e D11 respectivamente do Arduino. 
   O borne do Módulo referente ao MOTOR A deve ser ligado na fase A
   do motor de passo e o borne do MOTOR B na fase B. Já no borne 
   central do Módulo deve-se ligar o VMS na tensão positiva de uma 
   fonte externa de acordo com a capacidade dos motores. No GND do 
   borne central deve-se ligar o GND dessa mesma fonte externa. E o 
   GND do Arduino também deve ser interligado com o GND da fonte externa.
*/

/////////////////////////////////
// INICIALIZAÇÃO DAS VARIÁVEIS //
/////////////////////////////////     
char comando;
Servo myservo;
int CEN = 50;        // Direcao central 

int SRV=5;          // Define o pino 2 como o servo


// int IN1=8;           //inicializando variável denominada
                     //IN1 no pino digital 8 

// int IN2=9;           //inicializando variável denominada
                     //IN2 no pino digital 9 

int IN3=10;          //inicializando variável denominada
                     //IN3 no pino digital 10 

int IN4=11;          //inicializando variável denominada
                     //IN4 no pino digital 11 

int RD=A0;           //inicializa variavel denominada
                     //FD no pino analogico A0

int RE=A1;           //inicializa variavel denominada
                     //FD no pino analogico A1

int FD=A4;           //inicializa variavel denominada
                     //FD no pino analogico A0

int FE=A5;           //inicializa variavel denominada
                     //FD no pino analogico A1

int MD=A2;           //inicializa variavel denominada
                     //FD no pino analogico A0

int ME=A3;           //inicializa variavel denominada
                     //FD no pino analogico A1

int BUZ=12;            // Declara Buzina
                     
int velocidade = 5;

///////////
// SETUP //
///////////
void setup()
{
 //myservo.attach(2); // Inicializa controle do cervo no pino 2 
 pinMode(4,OUTPUT); //ENA
 pinMode(3,OUTPUT); //ENB

 analogWrite(3,160); // Velocidade dos motores aproximadamente 5V     
 analogWrite(4,160); // Velocidade dos motores aproximadamente 5V 
  
 // pinMode(IN1,OUTPUT); //configurando pino8(IN1)
                      //como uma SAÍDA digital.
 
 // pinMode(IN2,OUTPUT); //configurando pino9(IN2)
                      //como uma SAÍDA digital.
 
 pinMode(IN3,OUTPUT); //configurando pino10(IN3)
                      //como uma SAÍDA digital.
 
 pinMode(IN4,OUTPUT); //configurando pino11(IN4)
                      //como uma SAÍDA digital.


 pinMode(RD,OUTPUT); //configurando pinoA0(FD) Re direrita
                      //como uma SAÍDA digital.

 pinMode(RE,OUTPUT); //configurando pinoA0(FE) Re esquerda
                      //como uma SAÍDA digital.

 pinMode(FD,OUTPUT); //configurando pinoA0(FD) Farol Direito
                      //como uma SAÍDA digital.

 pinMode(FE,OUTPUT); //configurando pinoA0(FE) Farol Esquerdo

 pinMode(MD,OUTPUT); //configurando pinoA0(FD) Farol Milha Direito
                      //como uma SAÍDA digital.

 pinMode(ME,OUTPUT); //configurando pinoA0(FE) Farol Milha Esquerdo

 pinMode(BUZ,OUTPUT); // Pino 12 como buzzer
 
 Serial.begin(9600);
 
 NteSerial.begin(9600);
                
}


void loop()
{
 /*
   Para operar um motor DC é necessário alimentar suas bobinas com 
   Vcc e GND. Para fazê-lo girar em sentido contrário, basta inverter
   o Vcc com o GND.
   O controle de velocidade pode ser obtido conectando-se os pinos 
   ENA (ENB) a um pino PWM do Arduino e fazendo as devidas configurações
   na programação. 
   Veja abaixo uma sequência para operar os dois motores DC no mesmo sentido:
    Bobina A1  1 (HIGH)
    Bobina A2  0 (LOW)		
    Bobina B1  1 (HIGH)
    Bobina B2  0 (LOW)	
 */

if (NteSerial.available()) {

    comando = NteSerial.read();
    Serial.println(comando);
    switch(comando){
      case  'F': 
        Frente();
        break;
      case  'B':
        Re();
        break;             
      case  'R':
        VirarDireita();
        break;                         
      case  'L':
        VirarEsquerda();
        break;   
      case  'S':
        Parado();
        Centro();
        break;          
      case  'V':
        LigaBuzina();
        break;        
      case  'v':
        DesligaBuzina();
        break;
      case  'U':
        AcendeRe();
        break;
      case  'u':
        ApagaRe();
        break;
      case  'W':
        AcendeFarol();
        break;
      case  'w':
        ApagaFarol();
        break; 
      case  'X':
        LigaAlerta();
        break;
      case  'x':
        DesligaAlerta();
        break;         
    }
    
  }
}

      
void LigaBuzina(){
  tone(BUZ,262,1000);
  delay(600);
}

void DesligaBuzina(){
   
}

void Frente(){
   analogWrite(velocidade,160);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   digitalWrite(MD,HIGH);
   digitalWrite(ME,HIGH);   
}

void Re(){
  analogWrite(velocidade,100);     
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(RD,HIGH);
  digitalWrite(RE,HIGH);    
}

void Parado(){
  analogWrite(velocidade,0);       
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(MD,LOW);
  digitalWrite(ME,LOW);
  // digitalWrite(RD,LOW);
  // digitalWrite(RE,LOW);
}

void Centro(){
  myservo.attach(SRV);
  myservo.write(CEN);
  myservo.detach();
}

void VirarDireita(){
   // analogWrite(velocidade,100);       
   // digitalWrite(IN1,HIGH);
   // digitalWrite(IN2,LOW);  

   myservo.attach(SRV); 
   myservo.write(30); 
   delay(20);
   myservo.detach();
}

void VirarEsquerda(){
  // analogWrite(velocidade,100);         
  // digitalWrite(IN1,LOW);
  // digitalWrite(IN2,HIGH);  
  
  myservo.attach(SRV);
  myservo.write(55);
  delay(20);
  myservo.detach();   
}

void AcendeFarol(){
  digitalWrite(FD,HIGH);
  digitalWrite(FE,HIGH);
}
 
void ApagaFarol(){
  digitalWrite(FD,LOW);
  digitalWrite(FE,LOW);
}

void AcendeRe(){
  digitalWrite(RD,HIGH);
  digitalWrite(RE,HIGH);
}
 
void ApagaRe(){
  digitalWrite(RD,LOW);
  digitalWrite(RE,LOW);
}

void LigaAlerta()
{
   for (int i=0; i <= 255; i++){
      analogWrite(MD, i);
      analogWrite(ME, i);
      delay(10);
   } 
}

void DesligaAlerta()
{
    digitalWrite(MD,LOW);
    digitalWrite(ME,LOW);
}
