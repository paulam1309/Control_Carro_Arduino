#include <SoftwareSerial.h>
//Creación del Objeto Bluetooth
SoftwareSerial Bluetooth(10,11); //Pin 10 TX de Bluetooth, Pin 11 RX de bluetooth
//Varibles
char Texto=0;
int Velocidad = 200;
const int IN1 = 2;
const int IN2 = 3;
const int IN3 = 4;
const int IN4 = 5;
const int ENA = 6;
const int ENB = 7;
long Duracion, Distancia;
const int Echo = 8;
const int Trig = 9;
const int Buzzer = 12;
const int Led = 13;




//Setup
void setup() {
  Serial.begin(9600);
  Bluetooth.begin(38400);
  Inicializar_Pines(ENA,IN2,IN1,ENB,IN4,IN3,Echo,Trig,Buzzer,Led);
}

void loop() {
  if(Bluetooth.available()){
    Texto = Bluetooth.read();
    //Avanzar
    if((Texto=='1')){
      Adelante(Velocidad,ENA,IN2,IN1,ENB,IN4,IN3);
    }

    //Parar Avance
    if((Texto == '2')){
      Apagar(ENA,ENB);
    }
    
    //Derecha
    if(Texto == '7'){
      IrIzquierda(Velocidad,ENB,IN4,IN3);
    }

    //Parar Derecha
    if(Texto == '8'){
      Apagar(ENA,ENB);
    }
    
    //Izquierda
    if(Texto == '5'){
      IrDerecha(Velocidad,ENA,IN2,IN1);
    }

    //Parar Izquierda
    if(Texto == '6'){
      Apagar(ENA,ENB);
    }

    //Atras
    if(Texto == '3'){
      Retroceder(Velocidad,ENA,IN1, IN2,ENB,IN3,IN4);
      Sensor(Duracion,Distancia,Echo,Trig,Buzzer);
      Prender_Led(Led);
    }

    // Parar Atras
    if(Texto == '4'){
      Apagar(ENA,ENB);
      Apagar_Led(Led);
    }
    
  }

}


void Inicializar_Pines(int ENA, int IN1, int IN2, int ENB, int IN3, int IN4,int Echo, int Trig, int Buzzer, int Led){
  //Motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  //Sensor
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(Led, OUTPUT);
}
void Adelante_A(int Velocidad,int ENA, int IN1, int IN2){
  analogWrite(ENA,Velocidad);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
}
void Adelante_B(int Velocidad,int ENB, int IN3, int IN4){
  analogWrite(ENB,Velocidad);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void Adelante(int Velocidad,int ENA, int IN1, int IN2, int ENB, int IN3, int IN4){
  Adelante_A(Velocidad,ENA,IN1,IN2);
  Adelante_B(Velocidad,ENB,IN3,IN4);
}
void IrDerecha(int Velocidad,int ENA, int IN1, int IN2){
  Adelante_A(Velocidad,ENA,IN1,IN2);
}
void IrIzquierda(int Velocidad,int ENB, int IN3, int IN4){
  Adelante_B(Velocidad,ENB,IN3,IN4);
}
void Retroceder(int Velocidad,int ENA, int IN1, int IN2, int ENB, int IN3, int IN4){
  analogWrite(ENA,Velocidad);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENB,Velocidad);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void Apagar_A(int ENA){
  digitalWrite(ENA,LOW);
}
void Apagar_B(int ENB){
  digitalWrite(ENB,LOW);
}
void Apagar(int ENA, int ENB){
  Apagar_A(ENA);
  Apagar_B(ENB);
}

void Sensor(int Duracion, int Distancia, int Echo,int Trig,int Buzzer){
  //Mandar Pulso
  digitalWrite(Trig, LOW);
  delay(5);
  digitalWrite(Trig, HIGH);
  delay(10);
  digitalWrite(Trig, LOW);

  //Leer Pulso
  Duracion = pulseIn(Echo,HIGH);
  Distancia = (Duracion / 2) / 29; //Distancia en Cm
  Sensor_Sonar(Distancia,Buzzer);
}
void Probar_Sensor(int Distancia){
  if (Distancia >= 500 || Distancia <= 0){
    Serial.println("---");
  }
  else{
    Serial.print(Distancia);
    Serial.println ("cm");  
  }
  if(Distancia >=0 && Distancia <=10){
    Serial.println("Alarma");
  }
}
void Sensor_Sonar(int Distancia,int Buzzer){
  Serial.print(Distancia);
    Serial.println ("cm"); 
  if(Distancia >= 0 && Distancia <= 70){
    if(Distancia>=60){
      digitalWrite(Buzzer,HIGH);
      delay(500);
      digitalWrite(Buzzer, LOW);
      delay(500);
    }
    if(Distancia >=3 && Distancia <60){
      digitalWrite(Buzzer,HIGH);
      delay(500);
      digitalWrite(Buzzer, LOW);
      delay(500);
    }
  }
}
void Prender_Led(int Led){
  digitalWrite(Led, HIGH);
}void Apagar_Led(int Led){
  digitalWrite(Led, LOW);
}
