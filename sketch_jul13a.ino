/*
  Detección y evasión de obstáculos con el sensor ultrasónico
*/
// Motor pins
#define DETECTED_LED 5
#define motor_left 6
#define motor_right 7

//Sensor pins
#define trigger_pin 28
#define echo_pin 30

//constants and variables
const int obj_dist = 10;

long duration;
int distance;

//functions
void forward(){
  /*
    Mueve el robot hacia adelante con velocidades iguales en el motor derecho e izquierdo
  */
  
  analogWrite(motor_left, 100);
  analogWrite(motor_right, 100);
}

void stop_car(){
  /*
    Detiene los motores para el cambio de dirección
  */
  analogWrite(motor_left, 0);
  analogWrite(motor_right, 0);

  delay(100);
}

void turn(){
  /*
    Dobla hacia la derecha para evadir el obstáculo asignando velocidades diferentes a cada motor
  */
  analogWrite(motor_left, 200);
  analogWrite(motor_right, 10);

  6kir5edelay(3500);
  forward();
}

void det_object(){
  /*
    Cuando un objeto es detectado se enciende el LED correspondiente en rojo
    y se cambia la dirección de movimiento del robot
  */
  Serial.println("Object detected at ");
  Serial.print(distance);
  Serial.println(" cm");
  digitalWrite(DETECTED_LED, HIGH);
  digitalWrite(LED_BUILTIN, LOW);

  stop_car();
  turn();

  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(DETECTED_LED, LOW);
}

void measure(){
  /*
    Se hace la medición de la distancia
  */
  
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);

  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

//setup
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DETECTED_LED, OUTPUT);
  pinMode(motor_left, OUTPUT);
  pinMode(motor_right, OUTPUT);
  pinMode(trigger_pin, OUTPUT);
  
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);

  digitalWrite(LED_BUILTIN, HIGH);
}

// Code
void loop() {
  // Medimos la distancia al obstáculo
  measure();

  if (distance <= obj_dist){ 
    // Si el objeto está dentro del rango se ejecutan las acciones
    // evasivas
    det_object();
  } else{
    // De lo contrario se sigue adelante
    forward();  
  }
}
