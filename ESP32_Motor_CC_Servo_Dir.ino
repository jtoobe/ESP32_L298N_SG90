/*

Manejo de un motor de CC con un puente H L298N sin libreria
y un servo SG90 tambien sin libreria
Esto es para evitar un conflicto que se presenta al usar
las librerias: ESP32Servo y L298N.h

*/

// Motor
int ENA = 33;
int IN1 = 32;
int IN2 = 25;

int servoPin = 5;

// estos interruptores simulan el sensor de linea
int buttonPin = 14;  // mueve el servo hacia un lado
int buttonPin2 = 17;  // mueve el servo hacia el otro lado


void setup() {


  Serial.begin(115200);
  Serial.println("Manejo de un servo simultaneamente con un L298N");

  //turn off L13
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, LOW);

  pinMode(servoPin, OUTPUT);
  digitalWrite(servoPin, LOW);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  // Declaramos del puente H
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {

  // con la instruccion que sigue el motor gira hacia adelante todo el tiempo mientras no se indique lo contrario

  Adelante();

  // OJO con los valores "posicion" porque al manejarse directamente no hay limite y se puede romper el servo.


  Serial.print("un lado");
  while (digitalRead(buttonPin) == HIGH) {
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(1900);  //posicion
    digitalWrite(servoPin, LOW);
    delayMicroseconds(18100);  //frecuencia (depende del servo usado)
  }

  Serial.println("al centro");
  while (!digitalRead(buttonPin) == HIGH) {
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(100);  //posicion
    digitalWrite(servoPin, LOW);
    delayMicroseconds(18900);  // frecuencia (depende del servo usado)
  }

  Serial.print("al otro lado");
  while (digitalRead(buttonPin2) == HIGH) {
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(100);  //posicion
    digitalWrite(servoPin, LOW);
    delayMicroseconds(18100);  // frecuencia (depende del servo usado)
  }

  Serial.println("al centro");
  while (!digitalRead(buttonPin2) == HIGH) {
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(1900);
    digitalWrite(servoPin, LOW);
    delayMicroseconds(18900);
  }


  // otras funciones del motor
  //delay(1000);
  //Atras();
  //delay(1000);

  //Parar();
  //delay(1000);
}


void Adelante() {
  //Direccion Adelante
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 200);  //Velocidad motor (max 255, menos de 150 gira pero pierde potencia, probar)
}

void Atras() {
  //Direccion Atras
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 200);  //Velocidad motor 
}


void Parar() {
  //Detener motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);  //Velocidad motor 
}