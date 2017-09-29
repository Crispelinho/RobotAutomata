/*
 *     //     //   //       //  //////////  //      //         //\\\              ///////////
 *     //     //   ////     //      //      ////    ///        //  \\\            //         
 *     //     //   // //    //      //      // //   // //      //    \\\          //         
 *     //     //   //  //   //      //      //  //  //  //     //      \\\        ////////////
 *     //     //   //    // //      //      //   // //   //    //////////\\\      //        //
 *     //     //   //      ///      //      //     ///    //   //          \\\    //        //
 *     /////////   //       //  //////////  //      //     //  //            \\\  ////////////
 * 
 * 
 * Asignatura: Compiladores
 * 
 * Docente: Ing. Daniel Gonzalez Polo
 * 
 * Andrés Racines
 * Cristhian Carpio
 * Efraín García 
 * 
 * Ingeniería de Sistemas
 * Universidad del Magdalena
 * Copyright © 2017
 * 
 * ----------------------------------------
 */

#include <Regexp.h>

char readString;
int cont = 1;
int tam=0;
unsigned int count1=0;   
char c[100];
   
void setup() {
    Serial.begin(115200);
}

void imprimircadena(char c[]){
  //Serial.println(" cont= "+cont);
  char vacio[100]="";
  if(c[0]==vacio[0])
  {  Serial.println("Impresion de cadena vacia: ");

   }
   else
   {
      Serial.println("Impresion de cadena: ");
    for(int i=0;i<=cont;i++)
      {Serial.print(c[i]);
      }
    }
  Serial.println("");  
}

void reiniciar(char c[]){
    Serial.flush();
    readString = "";
    c="";
    cont = 1;
    delay(100);
    imprimircadena(c);
  }
  
void validar (char c[])
{   
    imprimircadena(c);
    MatchState ms;
    ms.Target (c);
    unsigned int count = ms.MatchCount ("[aeiou]");
    Serial.print ("Found ");
    Serial.println (count);

      if (count == 0)
      {   
          Serial.println("No es una expresion valida");
      }
      else
      {
          Serial.println("Expresion valida");
      }
}

void loop(){
   while (Serial.available() && cont>0) {
   delay(100);
   //Serial.print(cont);
    if (Serial.available() >0) {
       c[cont] = Serial.read();  //gets one byte from serial buffer
       readString += c[cont]; //makes the string readString
       }
     cont=cont+1;
   }

   char buf1 [100]="";
     for(int i=0;i<cont;i++)
    {buf1[i]=c[i+1];
    }
   
  if (cont >= 2){
        cont=cont-1;
        Serial.print(cont);
        Serial.println(" letras");
        validar(buf1);
        Serial.println("Limpieza");
        reiniciar(buf1);
        Serial.print("cont= ");
        Serial.println(cont);
    }
}
