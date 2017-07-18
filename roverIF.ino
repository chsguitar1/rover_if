/*
   Aula 71 - Robô com Motor Shield - Parte 1
        
   Autor: Eng. Wagner Rambo  Data: Junho de 2016
   Modificado por Cristiano Herculano da silva Julho de 2017
*/
 
// --- Bibliotecas Auxiliares ---
#include <AFMotor.h>         //Inclui biblioteca AF Motor
  
// --- Seleção dos Motores ---
// --- Seleção dos Motores ---
AF_DCMotor motorDirFrontal(1); //Seleção do Motor 1
AF_DCMotor motorEsqFrontal(2); //Seleção do Motor 2
AF_DCMotor motorDirTraz(4); //Seleção do Motor 4
AF_DCMotor motorEsqTraz(3); //Seleção do Motor 3
 

// --- Mapeamento de Hardware ---
 
// --- Protótipo das Funções Auxiliares ---
void robot_forward(unsigned char v);  //Função movimenta robô frente
void robot_backward(unsigned char v); //Função movimenta robô trás
void robot_left(unsigned char v);     //Função movimenta robô esquerda
void robot_right(unsigned char v);    //Função movimenta robô direita
void robot_stop(unsigned char v);     //Função para para o robô
 int r_stop;

 //---- Mudança nas variaves de moviomentação pela montagem do robo
int FRENTE = BACKWARD;
int TRAZ = FORWARD; 
int FREIAR = BRAKE;
int PARE =  RELEASE; 
         
// --- Variáveis Globais ---
unsigned char velocidade = 0x00; //armazena velocidade motores (8 bits)
          
// --- Configurações Iniciais ---
void setup()
{
  //A biblioteca configura as entradas e saídas pertinentes...  
  velocidade = 0xFF; //Inicia velocidade no valor máximo
  r_stop = 0;
} //end setup

 
// --- Loop Infinito ---
void loop()
{ 
     
     
     robot_forward(velocidade);
       delay(2000);
     
     
    
   
//     robot_backward(velocidade);
//     delay(500);
////     }
     
////      
//     robot_right(velocidade);
//     delay(500);
//      
//     robot_left(velocidade);
//     delay(500);
     
//     robot_stop(velocidade);
//     delay(500);
//  
} //end loop
 
 
// --- Desenvolvimento das Funções Auxiliares ---
 
void robot_backward(unsigned char v)
{
     motorDirFrontal.setSpeed(v);
     motorDirFrontal.run(FORWARD);
     motorEsqFrontal.setSpeed(v);
     motorEsqFrontal.run(FORWARD);
     motorDirTraz.setSpeed(v);
     motorDirTraz.run(FORWARD);
     motorEsqTraz.setSpeed(v);
     motorEsqTraz.run(FORWARD);
 
} //end robot forward
 
    
void robot_forward(unsigned char v)
{
     motorDirFrontal.setSpeed(v);
     motorDirFrontal.run(BACKWARD);
     motorEsqFrontal.setSpeed(v);
     motorEsqFrontal.run(BACKWARD);
     motorDirTraz.setSpeed(v);
     motorDirTraz.run(BACKWARD);
     motorEsqTraz.setSpeed(v);
     motorEsqTraz.run(BACKWARD);
    
 
} //end robot backward
 
 
 
void robot_left(unsigned char v)
{
  Serial.println("esquerda");
     motorDirFrontal.setSpeed(v);
     motorDirFrontal.run(FRENTE);
     motorEsqFrontal.setSpeed(v);
     motorEsqFrontal.run(TRAZ);
     motorDirTraz.setSpeed(v);
     motorDirTraz.run(FRENTE);
     motorEsqTraz.setSpeed(v);
     motorEsqTraz.run(TRAZ);
 
} //end robot left
 
 
void robot_right(unsigned char v)
{
   Serial.println("direita");
     motorDirFrontal.setSpeed(v);
     motorDirFrontal.run(TRAZ);
     motorEsqFrontal.setSpeed(v);
     motorEsqFrontal.run(FRENTE);
     motorDirTraz.setSpeed(v);
     motorDirTraz.run(TRAZ);
     motorEsqTraz.setSpeed(v);
     motorEsqTraz.run(FRENTE);
 
} 
 
void robot_stop(unsigned char v)
{
     motorDirFrontal.setSpeed(v);
     motorDirFrontal.run(RELEASE);
     motorEsqFrontal.setSpeed(v);
     motorEsqFrontal.run(RELEASE);
     motorDirTraz.setSpeed(v);
     motorDirTraz.run(RELEASE);
     motorEsqTraz.setSpeed(v);
     motorEsqTraz.run(RELEASE);
 
} //end robot stop
