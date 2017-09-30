

int izqA = 2; 
int izqB = 3; 
int derA = 4; 
int derB = 5; 
int vel = 255; // Velocidad de los motores (0-255)
int estado = 'g'; // inicia detenido
int pecho=10;
int ptrig=9;
int duracion,distancia;

void setup() { 
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
}
