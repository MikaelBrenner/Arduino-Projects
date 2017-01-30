#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 2, 3, 4, 5);

#define analogPin      0          // pino analógico a medir tensão no capacitor
#define chargePin      13         // pino a carregar o capacitor
#define dischargePin   11         // pino a descarregar o capacitor
#define resistorValue  1000  // mude esse valor para o valor do seu res

unsigned long startTime;
unsigned long elapsedTime;
double microFarads;                // variável ponto flutuante para efetuar os cálculos
double nanoFarads;

void setup(){

	pinMode(chargePin, OUTPUT);     // ajuste chargePin como saída
	digitalWrite(chargePin, LOW);  
	Serial.begin(9600);             // inicializa a comunicação serial para fins de depuração de erros
	lcd.begin(16, 2);
	lcd.print("OLA");
	delay(1000);
	lcd.clear();
  
}

void calc(unsigned long elapsedTime){

	microFarads = ((double)elapsedTime / resistorValue) * 1000;   
	if(microFarads >= 1){

		lcd.print(microFarads);
		lcd.setCursor(9,1);
		lcd.print("  uF");
	    lcd.setCursor(9,0);
		lcd.print("Aproximado");
		delay(1000);

	}else{

		nanoFarads = microFarads * 1000;
		lcd.print(nanoFarads);
		lcd.setCursor(9,1);
		lcd.print("  nF");
	  	lcd.setCursor(9,0);
		lcd.print("Aproximado")
		delay(1000);

	}
}

void ending(){

	digitalWrite(chargePin, LOW);             // ponha LOW em chargePin
    pinMode(dischargePin, OUTPUT);            // ajuste dischargePin como saída
	digitalWrite(dischargePin, LOW);          // ponha LOW
    while(analogRead(analogPin) > 0);         // espere até esvaziar capacitor
    pinMode(dischargePin, INPUT);
    lcd.clear();	

}

void loop(){

    digitalWrite(chargePin, HIGH);  
    startTime = millis();
    while(analogRead(analogPin) < 648);       // 647 = 63.2% de 1023, que corresponde ao fim de escala
	elapsedTime= millis() - startTime;
	calc(elapsedTime);
	ending();

}