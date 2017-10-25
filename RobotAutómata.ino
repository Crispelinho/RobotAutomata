/*
Controlar por Bluetooth el Arduino para aplicaciones como Carros, Brazos acrobáticos, Mandos a distancia, Automatizacion, etc...
Que envía esta App por el modulo Bluetooth:
Flecha Arriba = Caracter 'a'
Flecha Izquierda = Caracter 'b'
Boton Cuadrado = Caracter 'c'
Flecha Derecha = Caracter 'd'
Flecha Abajo = Caracter 'e'
Boton ON = Caracter 'f'
Boton OFF = Caracter 'g'
Boton Bluetooth = Es para seleccionar el Modulo Bluetooth a que se va a conectar 
(El modulo bluetooth debe estar previamente sincronizado con su telefono Android

Para realizar Pruebas conecte LEDs a los puertos PWM 5, 6, 9, 10 del Arduino, en el proyecto final a esos puertos se conecta el puente H, Cargue al Arduino el siguiente codigo:
*/
#include <Servo.h>
Servo miServo;
int pos1 = 50;
int pos2 = 90;
int pos3 = 130;
int izqA = 2; 
int izqB = 3; 
int derA = 4; 
int derB = 5; 
int vel = 255; // Velocidad de los motores (0-255)
int estado = 'g'; // inicia detenido
int pecho=10;
int ptrig=9;
int PIN_TRIG =9; 
int PIN_ECO =10;
int duracion,distancia;
float d1, d2;
void setup() { 
miServo.attach(6); //Servo en el Pin6.
Serial.begin(9600); // inicia el puerto serial para comunicacion con el Bluetooth
pinMode(11, OUTPUT);
pinMode(derA, OUTPUT);
pinMode(derB, OUTPUT);
pinMode(izqA, OUTPUT);
pinMode(izqB, OUTPUT);

pinMode(pecho, INPUT);
pinMode(ptrig, OUTPUT);
pinMode(13, OUTPUT);
} 


//_____________________________________________________________________________________
//  FUNCIONES PARA CONTROL DE MOTORES
//-------------------------------------------------------------------------------------

void ADELANTE() {
  digitalWrite(izqA, vel);
  digitalWrite(izqB, 0);
  digitalWrite(derA, vel);
  digitalWrite(derB, 0);
}

void STOP() {
  digitalWrite(izqA, 0);
  digitalWrite(izqB, 0);
  digitalWrite(derA, 0);
  digitalWrite(derB, 0);
  delay(10);
}

void STOP1() {
  digitalWrite(izqA, 0);
  digitalWrite(izqB, 0);
  digitalWrite(derA, 0);
  digitalWrite(derB, 0);
  delay(100);
}


void RETROCEDER() {
  digitalWrite(izqA, 0);
  digitalWrite(izqB, vel);
  digitalWrite(derA, 0);
  digitalWrite(derB, vel);
  delay(500);
}

void RETROCEDER1() {
  digitalWrite(izqA, 0);
  digitalWrite(izqB, vel);
  digitalWrite(derA, 0);
  digitalWrite(derB, vel);
  delay(60);
}

void DERECHA() {
  digitalWrite(izqA, 0);
  digitalWrite(izqB, 0);
  digitalWrite(derA, vel);
  digitalWrite(derB, 0);
  delay(220);
}

void IZQUIERDA() {
  digitalWrite(izqA, vel);
  digitalWrite(izqB, 0);
  digitalWrite(derA, 0);
  digitalWrite(derB, 0);
  delay(220);
}

void loop() { 
 digitalWrite(11,HIGH);
if(Serial.available()>0){ // lee el bluetooth y almacena en estado
estado = Serial.read();
}
  if(estado=='a'){ // Boton desplazar al Frente
  analogWrite(derB, 0); 
  analogWrite(izqB, 0); 
  analogWrite(derA, vel); 
  analogWrite(izqA, vel); 
  }

  if(estado=='b'){ // Boton IZQ 
  analogWrite(derB, 0); 
  analogWrite(izqB, 0); 
  analogWrite(derA, 0); 
  analogWrite(izqA, vel); 
  }
   
   if(estado=='c'){ // Boton Parar
   analogWrite(derB, 0); 
   analogWrite(izqB, 0); 
   analogWrite(derA, 0); 
   analogWrite(izqA, 0); 
    }
   
   if(estado=='d'){ // Boton DER
   analogWrite(derB, 0); 
   analogWrite(izqB, 0);
   analogWrite(izqA, 0);
   analogWrite(derA, vel); 
    } 

    if(estado=='e'){ // Boton Reversa
    analogWrite(derA, 0); 
    analogWrite(izqA, 0);
    analogWrite(derB, vel); 
    analogWrite(izqB, vel); 
    }
    
    if (estado =='f'){ // Boton ON se mueve sensando distancia 

    long duracion, distancia;
    miServo.write(pos2); // centrando el servomotor
    delay(50);
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    duracion = pulseIn(PIN_ECO, HIGH); // guarda el tiempo que demora en llegar el pulso
    distancia = (duracion / 2) / 29;

    if (distancia > 40) {
      
  analogWrite(derB, 0); 
  analogWrite(izqB, 0); 
  analogWrite(derA, vel); 
  analogWrite(izqA, vel);
    }

    if (distancia <= 40) {
    analogWrite(derA, 0); 
    analogWrite(izqA, 0);
    analogWrite(derB, vel); 
    analogWrite(izqB, vel); 
    delay(60);
   analogWrite(derB, 0); 
   analogWrite(izqB, 0); 
   analogWrite(derA, 0); 
   analogWrite(izqA, 0); 
   delay(100);
      //Medición de la distancia del lado izquierdo
      miServo.write(pos3); //Servo hacia la izquierda
      delay(200);
      digitalWrite(PIN_TRIG, LOW);
      delayMicroseconds(2);
      digitalWrite(PIN_TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(PIN_TRIG, LOW);
      duracion = pulseIn(PIN_ECO, HIGH); // guarda el tiempo que demora en llegar el puls
      d1 = (duracion / 2) / 29; //ara la distan en cm hacia la izquierda
      //Ahora se mide la distancia del lado derecho
      miServo.write(pos1); //Servo hacia la derecha
      delay(200);
      digitalWrite(PIN_TRIG, LOW);
      delayMicroseconds(2);
      digitalWrite(PIN_TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(PIN_TRIG, LOW);
      duracion = pulseIn(PIN_ECO, HIGH); //guarda el tiempo que demora en llegar el puls
      d2 = (duracion / 2) / 29; //guara la distan en cm (1/29 cm/us)
      // y dos debido a que el tiempo de
      //duracion es el doble porque recorre
      //ida y vuelta por ello dividimos entre 2//

      if (d1 > d2) { //girando hacia la izquiera
        miServo.write(pos2); // centrando el servomotor
        delay(100);
  analogWrite(derB, 0); 
  analogWrite(izqB, 0); 
  analogWrite(derA, 0); 
  analogWrite(izqA, vel); 
   delay(220);
   analogWrite(derB, 0); 
   analogWrite(izqB, 0); 
   analogWrite(derA, 0); 
   analogWrite(izqA, 0); 
   delay(10);
      }

      if (d2 > d1) { //girando hacia la derecha
        miServo.write(pos2); // centrando el servomotor
        delay(100);
   analogWrite(derB, 0); 
   analogWrite(izqB, 0);
   analogWrite(izqA, 0);
   analogWrite(derA, vel); 
   delay(220);
   analogWrite(derB, 0); 
   analogWrite(izqB, 0); 
   analogWrite(derA, 0); 
   analogWrite(izqA, 0); 
   delay(10);
      }

      if (d1 <= 40 && d2 <= 40) { // compara si la distancia de la izquierda y la derecha son menores a 30 si esto pasa retrocedera
        miServo.write(pos2); // centrando el servomotor
        delay(100);
        
    analogWrite(derA, 0); 
    analogWrite(izqA, 0);
    analogWrite(derB, vel); 
    analogWrite(izqB, vel); 
        delay(500);
   analogWrite(derB, 0); 
   analogWrite(izqB, 0);
   analogWrite(izqA, 0);
   analogWrite(derA, vel); 
        delay(220);
   analogWrite(derB, 0); 
   analogWrite(izqB, 0); 
   analogWrite(derA, 0); 
   analogWrite(izqA, 0); 
        delay(10);
      }

      if (d1 > 450 && d2 > 450) {
        miServo.write(pos2);
        delay(100);
    analogWrite(derA, 0); 
    analogWrite(izqA, 0);
    analogWrite(derB, vel); 
    analogWrite(izqB, vel); 
    delay(500);
  analogWrite(derB, 0); 
  analogWrite(izqB, 0); 
  analogWrite(derA, 0); 
  analogWrite(izqA, vel); 
   delay(220);
   analogWrite(derB, 0); 
   analogWrite(izqB, 0); 
   analogWrite(derA, 0); 
   analogWrite(izqA, 0); 
   delay(10);
      }
    }  
  }

    if (estado=='g'){ // Boton OFF, detiene los motores no hace nada 
      analogWrite(derB,0);
      analogWrite(izqB,0);
      analogWrite(derA,0);
      analogWrite(izqA,0);  
     }
}
