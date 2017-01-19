//Written by Mikael Brenner and Henrique de Souza
//Escrito por Mikael Brenner e Henrique de Souza
//January of 2017
//Janeiro de 2017
//Published under The GNU General Public License v3.0

#include <Servo.h>

#define SERVA 8
#define SERVB 9     //Define os pinos aos quais os servos estão conectados
#define SERVC 10
#define SERVD 11
#define SERVE 12

char SERVATUAL;     //Container para segurar qual o servo selecionado via serial
int POSATUAL;     //Container para segurar o valor da posição do servo
char RCV[3];      //Array de 3 posições para segurar o valor da posição recebido via serial

Servo servoA;
Servo servoB;
Servo servoC;     //Criação dos servos
Servo servoD;
Servo servoE;

void setup() {
  servoA.attach(SERVA);
  servoB.attach(SERVB);
  servoC.attach(SERVC);     //Vinculando os servos aos pinos correspondentes
  servoD.attach(SERVD);
  servoE.attach(SERVE);
  Serial.begin(9600);     //Inicializando a comunicação serial
}

void servotest(Servo &theServo){      //Função responsável por atribuir a posição desejada ao servo
  for (int i = 0; i < 3; i++) {     //Loop responsável por ler os bytes recebidos via serial
      RCV[i] = Serial.read();     //Atribuindo-os a posições do array RCV
  }
  POSATUAL = atoi(RCV);     //Converte os 3 dígitos para um único inteiro
  theServo.write(POSATUAL);     //Envia a posição, já inteira, para o servo
  Serial.print(SERVATUAL);      //Escreve no monitor serial qual o valor de servo recebido
  Serial.println(POSATUAL);     //Escreve no monitor serial qual a posição recebida
}

void loop() {
    while(!Serial.available());     //Segura o loop até haver algo na porta serial
    delay(50);      //Dá tempo para que o buffer encha 
    switch (Serial.peek()) {      //Analisa o primeiro dígito recebido via serial
        case 'A': SERVATUAL = Serial.read();      
                  servotest(servoA);
                  break;
        case 'B': SERVATUAL = Serial.read();
                  servotest(servoB);
                  break;
        case 'C': SERVATUAL = Serial.read();        //Chama a função servotest para o servo especificado via Serial
                  servotest(servoC);
                  break;
        case 'D': SERVATUAL = Serial.read();
                  servotest(servoD);
                  break;
        case 'E': SERVATUAL = Serial.read();
                  servotest(servoE);
                  break;
        default:      //Caso não seja um dos valores especificados esvazia o buffer
            do{
                Serial.read();      
            }while (Serial.available() > 0);
            break;
    }
}
