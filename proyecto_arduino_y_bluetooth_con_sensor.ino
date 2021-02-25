//INCLUIMOS LA LIBRERIA DEL BLUETOOTH
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//DECLARAMOS EL BLUETOOTH SERIAL
BluetoothSerial SerialBT;
//DECLARAMOS LOS PINES TANTO DEL SENSOR DE SONIDO COMO LOS LEDS

int MIC = 26;        // D0 de modulo a pin 2
int LED = 5;
int LED1 = 13;// anodo de LED a pin 3
int VALOR;        // variable para almacenar valor de D0
int ESTADO;       // variable para almacenar estado del LED
int op;

void setup(){
  Serial.begin(115200);
   SerialBT.begin("ESP32test");
  pinMode(MIC, INPUT);      // pin 26 como entrada
  pinMode(LED, OUTPUT);     // pin 5 como salida
  pinMode(LED1, OUTPUT); // pin 13 como salida
}


void loop(){
  //DECLARAMOS LOS METODOS DEL BLUETOOTH SERIAL
  if (SerialBT.available()) {
    SerialBT.write(Serial.read());
  }
   if(SerialBT.available()){
    op=SerialBT.read(); //capturamos el valor de la variable op
    SerialBT.write(op); //imprimimos el valor
    if (op == 'A') {   //ponemos la condicion de que si es igual a "A" vamos a encender los leds
      digitalWrite(LED, HIGH);
      Serial.println("Encender Led verde");
      digitalWrite(LED1, HIGH);
      Serial.println("Encender Led rojo");
    }
    else if (op == 'B') {   //ponemos la condicion de que si es igual a "B" vamos a apagar los leds
      digitalWrite(LED, LOW);
      Serial.println("Apagar Led verde");
      digitalWrite(LED1, LOW);
      Serial.println("Apagar Led ROJO");
    }
  }
  //EN LA VARIABLE VALOR QUE LEEMOS DEL PIN 26
  VALOR = digitalRead(MIC);   // obtiene valor de D0
  /*CONSULTAMOS CON EL IF SI EL VALOR ES 0 O 1 YA QUE SI ES 0 
  SIGNIFOCA QUE EL SENSOR NO HA ACTIVADO LA SALIDA DIGITAL 
  Y SI ES 1 ES QUE ESTA ACTIVA LA SALIDA O LO QUE ES 
  EQUIVALENTE A QUE EL NIVEL DE SONIDO CAPTADO HA SUPERADO EL UMBRAL 
  QUE ESTABLECIMOS CON EL PRESENTE*/
  if (VALOR == HIGH){     // CONOCER SI EL LED SE ENCUENTRA ENCENDIDO O APAGADO
    ESTADO = digitalRead(LED);    // almacena estado del led (encendido o apagado) declaramos la opcion opuesta si esta encendido lo apagamos y si esta apagado lo encendemos
    digitalWrite(LED, !ESTADO);   // escribe en LED el valor opuesto al que tenia
    delay(500);       // demora de medio seg. para evitar pulsos espureos
    ESTADO = digitalRead(LED1);    // almacena estado del led (encendido o apagado)
    digitalWrite(LED1, !ESTADO);   // escribe en LED el valor opuesto al que tenia
    delay(500);
  }
  
}
