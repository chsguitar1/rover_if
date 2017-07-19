                                                                      /*
   Curso de Arduino e AVR WR Kits Channel
   
   Aula 71 - Robô Completo com Motor Shield
   
    
   Autor: Eng. Wagner Rambo  Data: Junho de 2016
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits
   
*/


// --- Bibliotecas Auxiliares ---
#include <AFMotor.h>         //Inclui biblioteca AF Motor
#include <Servo.h>           //Inclui biblioteca para controle de Servos
 

// --- Seleção dos Motores ---
AF_DCMotor motorDirFrontal(1); //Seleção do Motor 1
AF_DCMotor motorEsqFrontal(2); //Seleção do Motor 2
AF_DCMotor motorDirTraz(4); //Seleção do Motor 4
AF_DCMotor motorEsqTraz(3); //Seleção do Motor 3
 


// --- Mapeamento de Hardware ---
#define   serv        10                 //controle do Servo 1
#define   trig        A4                 //Saída para o pino de trigger do sensor
#define   echo        A5                 //Entrada para o pino de echo do sensor
#define   buzzer        A2                 //Entrada para o pino de echo do sensor




// --- Protótipo das Funções Auxiliares ---
float measureDistance();                //Função para medir, calcular e retornar a distância em cm
void trigPulse();                       //Função que gera o pulso de trigger de 10µs
void decision();                        //Função para tomada de decisão. Qual melhor caminho?
void robot_forward(unsigned char v);    //Função para movimentar robô para frente
void robot_backward(unsigned char v);   //Função para movimentar robô para trás
void robot_left(unsigned char v);       //Função para movimentar robô para esquerda
void robot_right(unsigned char v);      //Função para movimentar robô para direita
void robot_stop(unsigned char v);       //Função para parar o robô


// --- Objetos ---
Servo servo1;                           //Cria objeto para o servo motor


// --- Variáveis Globais ---
unsigned char velocidade = 0x00;       //Armazena a velocidade dos motores (8 bits)
float dist_cm;                         //Armazena a distância em centímetros entre o robô e o obstáculo
float dist_right;                      //Armazena a distância em centímetros da direita
float dist_left;                       //Armazena a distância em centímetros da esquerda

//---- Mudança nas variaves de moviomentação pela montagem do robo
int FRENTE = BACKWARD;
int TRAZ = FORWARD; 
int FREIAR = BRAKE;
int PARE =  RELEASE; 
         
// --- Configurações Iniciais ---
void setup()
{

  //A biblioteca configura as entradas e saídas pertinentes ao Motor Shield...  
  
 Serial.begin(9600); 
 
 
 pinMode(trig, OUTPUT);                       //Saída para o pulso de trigger
 pinMode(serv, OUTPUT);                       //Saída para o servo motor
 pinMode(echo, INPUT);                        //Entrada para o pulso de echo
 pinMode(buzzer, OUTPUT); 
 
 servo1.attach(serv);                         //Objeto servo1 no pino de saída do servo
   
 digitalWrite(trig, LOW);                     //Pino de trigger inicia em low
   
 servo1.write(100);                            //Centraliza servo
  
 delay(500);                                  //Aguarda meio segundo antes de iniciar
  
  velocidade = 0xFF; //Inicia velocidade no valor máximo
  
  
} //end setup


// --- Loop Infinito ---
void loop()
{
  
  
    
     robot_forward(velocidade);
     delay(80);
  
     dist_cm = measureDistance();
  
     if(dist_cm < 20) //distância menor que 20 cm?
     {
         decision();
     }
     
    
 
} //end loop




// --- Desenvolvimento das Funções Auxiliares ---



float measureDistance()                       //Função que retorna a distância em centímetros
{
  float pulse;                                //Armazena o valor de tempo em µs que o pino echo fica em nível alto
        
  trigPulse();                                //Envia pulso de 10µs para o pino de trigger do sensor
  
  pulse = pulseIn(echo, HIGH);                //Mede o tempo em que echo fica em nível alto e armazena na variável pulse
    
  /*
    >>> Cálculo da Conversão de µs para cm:
    
   Velocidade do som = 340 m/s = 34000 cm/s
   
   1 segundo = 1000000 micro segundos
   
      1000000 µs - 34000 cm/s
            X µs - 1 cm
            
                  1E6
            X = ------- = 29.41
                 34000
                 
    Para compensar o ECHO (ida e volta do ultrassom) multiplica-se por 2
    
    X' = 29.41 x 2 = 58.82
 
  */
 // Serial.println(pulse/58.85);
  return (pulse/58.82);                      //Calcula distância em centímetros e retorna o valor
  
  
} //end measureDistante


void trigPulse()                             //Função para gerar o pulso de trigger para o sensor HC-SR04
{
   digitalWrite(trig,HIGH);                  //Saída de trigger em nível alto
   delayMicroseconds(10);                    //Por 10µs ...
   digitalWrite(trig,LOW);                   //Saída de trigger volta a nível baixo

} //end trigPulse


void decision()                              //Compara as distâncias e decide qual melhor caminho a seguir
{
   robot_stop(velocidade);                   //Para o robô
   delay(500);                               //Aguarda 500ms
   servo1.write(0);                          //Move sensor para direita através do servo
   delay(500);                               //Aguarda 500ms
   dist_right = measureDistance();           //Mede distância e armazena em dist_right
   delay(2000);                              //Aguarda 2000ms
   servo1.write(175);                        //Move sensor para esquerda através do servo
   delay(500);                               //Aguarda 500ms
   dist_left = measureDistance();            //Mede distância e armazena em dis_left
   delay(2000);                               //Aguarda 2000ms
   servo1.write(100);                         //Centraliza servo
   delay(500);
   Serial.println(dist_right);
Serial.println(dist_left);
   if(dist_right > dist_left)                //Distância da direita maior que da esquerda?
   {                                         //Sim...
      robot_backward(velocidade);
      //Move o robô para trás
     
      delay(600);                            //Por 600ms
      robot_right(velocidade);               //Move o robô para direita
      delay(2000);                           //Por 2000ms
      robot_forward(velocidade);             //Move o robô para frente
   
   }   
   else                                      //Não...
   {
   
      robot_backward(velocidade); 
     
      delay(600);                            //Por 600ms
     robot_left(velocidade);                //Move o robô para esquerda
      delay(2000);                            //Por 2000ms
      robot_forward(velocidade);              //Move o robô para frente
   
   } //end else
   dist_left = 0.0;
   dist_right = 0.0;

} //end decision

 
void robot_backward(unsigned char v)
{
  

     motorDirFrontal.setSpeed(v);
     motorDirFrontal.run(TRAZ);
     motorEsqFrontal.setSpeed(v);
     motorEsqFrontal.run(TRAZ);
     motorDirTraz.setSpeed(v);
     motorDirTraz.run(TRAZ);
     motorEsqTraz.setSpeed(v);
     motorEsqTraz.run(TRAZ);
 
} //end robot forward
 
    
void robot_forward(unsigned char v)
{
     motorDirFrontal.setSpeed(v);
     motorDirFrontal.run(FRENTE);
     motorEsqFrontal.setSpeed(v);
     motorEsqFrontal.run(FRENTE);
     motorDirTraz.setSpeed(v);
     motorDirTraz.run(FRENTE);
     motorEsqTraz.setSpeed(v);
     motorEsqTraz.run(FRENTE);
    
 
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
 
} //end robot right
 
 
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

