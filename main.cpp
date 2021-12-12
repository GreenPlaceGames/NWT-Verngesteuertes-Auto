#define IR_INPUT_PIN 3U          // Definiere Input Pin für Infra Rot
#define SERV_PIN 5U              // Definiere Output Pin für Servo
#define MOTOR_PIN_1 11U          // Definiere 1. Pin für Motorsteuerung
#define MOTOR_PIN_2 10U          // Definiere 2. Pin für Motorsteuerung
#define MOTOR_ENABLE_PIN 7U      // Definiere Pin für MotorEnable H-Brücke

#include <Servo.h>              // Binde Servo.h Library ein
#include <IRremote.h>           // Binde IRremote.h Library ein


IRrecv irrecv(IR_INPUT_PIN);    // Setze Variable irrecv gleich IR_INPUT_PIN
decode_results results;         // Lege Variable results fest

Servo servo;                    // Lege Variable servo fest
int count;                      // Lege Variable count als integer fest

void setup(){
  pinMode(MOTOR_PIN_1,OUTPUT);        // Setze pinMode von Pin MOTOR_PIN_1 auf OUTPUT
  pinMode(MOTOR_PIN_2,OUTPUT);        // Setze pinMode von Pin MOTOR_PIN_2 auf OUTPUT
  pinMode(MOTOR_ENABLE_PIN, OUTPUT);  // Setze pinMode von Pin MOTOR_ENABLE_PIN auf OUTPUT

  irrecv.enableIRIn();                // Starte den Empfang von Daten aus Infrarot Sensor

  servo.attach(SERV_PIN);             // Setze den output von Servo funktionen gleich dem SERV_PIN Pin
  servo.write(45);                    // Rotiere den Servo auf die 45 Grad Position

  Serial.begin(9600);
}
 
void loop(){
  digitalWrite(MOTOR_ENABLE_PIN, HIGH);     // Setze MOTOR_ENABLE_PIN auf HIGH

  int input = inputIR();                    // Definiere integer input
  if(input != -1){                          // Frage auf input ungleich -1 ab
    controllServo(input);                   // Ruft Funktion controllServo mit dem Parameter inputIR auf
    controllMotor(input);                   // Ruft Funktion controllMotor mit dem Parameter inputIR auf
  }
}

int inputIR()                                             // Definiere inputIR vom Datentyp float
{
  int retval;                                             // Definiere retval als integer
    if(irrecv.decode(&results))                           // Frage auf Input von Infrarot ab
    {
      count = 0;                                          // Setze count gleich 0
      if(results.value != 4294967295)                     // Frage auf bestimmtes ergebniss ab, wenn das nicht ist dann...
      {
        retval = (int)results.value;                      // ...setze retval gleich results
      }
      irrecv.resume();                                    // Beende Infrarot Reciever
    }else{                                                // Sonst...
      count++;                                            // Addire 1 zu count
      if(count == 50){                                    // Falls count gleich 50
        retval = 1;                                       // Setze retval auf 1
      }
    }
    Serial.println(retval, DEC);                          // Schreibe retval auf dem Seriellem Monitor aus
    return retval;                                        // Setze inputIR gleich retval
  }


void controllServo(int _input)        // Definiere die Funktion controllServo
{
  switch(_input){                     // Switch case statement mit int _input
    case 16716015:                    // Falls _input gleich 16716015...
      servo.write(90);                // ...setze Servo Position auf 90 Grad
      break;
    case 16734885:                    // Falls _input gleich 16734885...
      servo.write(0);                 // ...setze Servo position auf 0 Grad
      break;
    case 1:                           // Falls _input gleich 1...
      servo.write(45);                // ...setze Servo auf position 45 Grad
      break;
  }
}

void controllMotor(int _input)            // Definiere die Funktion controllMotor
{
  switch(_input){                         // Switch case statement mit int _input
    case 16718055:                        // Falls _input gleich 16718055...
      analogWrite(MOTOR_PIN_1, 0);        // ...Setze MOTOR_PIN_1 auf 255
      analogWrite(MOTOR_PIN_2, 255);      // ...und MOTOR_PIN_2 auf 0
      break;
    case 16730805:                        // Falls _input gleich 16730805...
      analogWrite(MOTOR_PIN_1, 255);      // ...Setze MOTOR_PIN_1 auf 0
      analogWrite(MOTOR_PIN_2, 0);        // ...und MOTOR_PIN_2 auf 255
      break;
    case 16732845:                        // Falls _input gleich 16732845
      analogWrite(MOTOR_PIN_1, 0);        // ... setze MOTOR_PIN_1 auf 0
      analogWrite(MOTOR_PIN_2, 0);        // ... und MOTOR_PIN_2 auf 0
      break;
  }
}
