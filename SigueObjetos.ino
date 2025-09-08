#include <Wire.h>

const int TrigC=3;
const int EchC=2;

const int TrigI=5;
const int EchI=4;

const int TrigD=6;
const int EchD=7;

const int MDF=8;
const int MDB=11;
const int MDENB=9;

const int MIF=12;
const int MIB=13;
const int MIENB=10;

/*
Suponiendo Arduino UNO

-----Conexión Ultrasonidos-----
    Echo-2                      Trigger-3
    VIN-5V                      
    GND-GND

    Echo-4                      Trigger-5
    VIN-5V                      
    GND-GND

    Echo-6                      Trigger-7
    VIN-5V                      
    GND-GND

-----Conexión Motores-----
    Derecho (Puente H)
    Movimiento hacia adelante-8        Movimiento hacia atrás-11
    ENB-9

    Izquierdo (Puente H)
    Movimiento hacia adelante-12        Movimiento hacia atrás-13
    ENB-10
*/
long dist(int trigger, int echo);
void girarDerecha();
void girarIzquierda();
void Avanti();
void Stop();

void setup() {
  // put your setup code here, to run once:
  //Esta secuencia es para checkear que funciona el módulo de color.
  Serial.begin(9600);


  //Configurar los ultrasonidos.
  pinMode(TrigC, OUTPUT);
  pinMode(EchC, INPUT);

  pinMode(TrigI, OUTPUT);
  pinMode(EchI, INPUT);

  pinMode(TrigD, OUTPUT);
  pinMode(EchD, INPUT);


  //Configurar motores.
  pinMode(MDF, OUTPUT);
  pinMode(MDB, OUTPUT);
  pinMode(MDENB, OUTPUT);

  digitalWrite(MDF, HIGH);
  digitalWrite(MDB, LOW);

  pinMode(MIF, OUTPUT);
  pinMode(MIB, OUTPUT);
  pinMode(MIENB, OUTPUT);

  digitalWrite(MIF, HIGH);
  digitalWrite(MIB, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Calculamos las distancias de los ultrasonidos.
  long dC, dI, dD;
  dC = dist(TrigC, EchC);
  dI = dist(TrigI, EchI);
  dD = dist(TrigD, EchD);
  Serial.print("DistC: ");
  Serial.println(dC);
  Serial.print("DistD: ");
  Serial.println(dD);
  Serial.print("DistI: ");
  Serial.println(dI);

  //¿Es el color correcto?
  if (dC >= 5 && dC < 15){
      //Motores hacia adelante
      Avanti();
      Serial.println("Av");
    }else if(dC < 5){
      Stop();
      Serial.println("ST");
    }else if (dD < 10){
      //Giro derecha
      girarDerecha(150);
      Serial.println("Der");
    } else if (dI < 10){
      //Giro izquierda
      girarIzquierda(150);
      Serial.println("Izq");
    } else{
     /*do{
      girarDerecha(100);
      Serial.println("Derer");
      dC = dist(TrigC, EchC);
      dI = dist(TrigI, EchI);
      dD = dist(TrigD, EchD);
      }while(!(dC < 10 || dI < 5 || dD < 5));*/
      Stop();
    }
}

long dist(int trigger, int echo){
  long t;
  long d;
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  t = pulseIn(echo, HIGH);
  d = 0.0172*t;
  return d;
}

void girarDerecha(int V){
  digitalWrite(MDF, LOW);
  digitalWrite(MDB, HIGH);
  digitalWrite(MIF, HIGH);
  digitalWrite(MIB, LOW);
  analogWrite(MDENB, V);
  analogWrite(MIENB, V);
}

void girarIzquierda(int V){
  digitalWrite(MDF, HIGH);
  digitalWrite(MDB, LOW);
  digitalWrite(MIF, LOW);
  digitalWrite(MIB, HIGH);
  analogWrite(MDENB, V);
  analogWrite(MIENB, V);
}

void Avanti(){
  digitalWrite(MDF, HIGH);
  digitalWrite(MDB, LOW);
  digitalWrite(MIF, HIGH);
  digitalWrite(MIB, LOW);
  analogWrite(MDENB, 250);
  analogWrite(MIENB, 250);
}
void Stop(){
  digitalWrite(MDF, HIGH);
  digitalWrite(MDB, LOW);
  digitalWrite(MIF, HIGH);
  digitalWrite(MIB, LOW);
  analogWrite(MDENB, 0);
  analogWrite(MIENB, 0);
}