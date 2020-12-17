//Enable(s) for motors
#define enA 5
#define enB 6

//Motor pins
#define in1 8
#define in2 9

#define in3 10
#define in4 11

//Senzor pins
#define sens1 2
#define sens2 3
#define sens3 4
#define sens4 7
#define sens5 12
/*****************
 * 
 *  MERGE CU: (minus insteamna motoarele pe reverse)
 *  200, -50
 * 
 * ***************
 */
int motorSpeedA = 0;
int motorSpeedB = 0;
int x = 999;
int lastCurve = 1;
int speed1 = 200, speed2 = 50 ;

void setup() {
  //Motor pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  //Senzor pins
  pinMode(sens1, INPUT);
  pinMode(sens2, INPUT);
  pinMode(sens3, INPUT);
  pinMode(sens4, INPUT);
  pinMode(sens5, INPUT);

  Serial.begin(9600);
}

void loop() {
  int v[6]{}; 
  readSens(v);
 
  x = determineDirection(v);
  setDirection(determineDirection(v));
  
  printSensors(v);
  

}

void setDirection(int lastDirection){
  switch (x){
    case -1:
      goLeft();
      lastDirection = -1;
      lastCurve = -1;
      break;
    case  0:
      goForward();
      lastDirection = 0;
      break;
    case  1:
      goRight();
      lastDirection = 1;
      lastCurve = 1;
      break;
   }
  //Serial.println(lastCurve);
  }



void readSens(int v[6]){
  v[1]=!digitalRead(sens1); v[2]=!digitalRead(sens2); v[3]=!digitalRead(sens3); v[4]=!digitalRead(sens4); v[5]=!digitalRead(sens5);
  }


void goForward() {
  //Motor left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW );
  analogWrite (enA, speed1);
  //Motor right
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW );
  analogWrite (enB, speed1);
}

void goLeft() {
  //Motor left
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite (enA, speed2);
  //Motor right
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW );
  analogWrite (enB, speed1);
}

void goRight() {
  //Motor left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW );
  analogWrite (enA, speed1);
  //Motor right
  digitalWrite(in3, LOW );
  digitalWrite(in4, HIGH);
  analogWrite (enB, speed2);
}

void goBackwards() {
  //Motor left
  digitalWrite(in1, LOW );
  digitalWrite(in2, HIGH);
  analogWrite (enA, speed1);
  //Motor right
  digitalWrite(in3, LOW );
  digitalWrite(in4, HIGH);
  analogWrite (enB, speed1);
}

void printSensors(int v[6]){
  Serial.print(v[1]);
  Serial.print(" ");
  Serial.print(v[2]);
  Serial.print(" ");
  Serial.print(v[3]);
  Serial.print(" ");
  Serial.print(v[4]);
  Serial.print(" ");
  Serial.print(v[5]);
  Serial.println();
}

int determineDirection(int v[6]){
    int op; //operation
     if((v[1] == 1 )&&(v[2] == 0 )&&(v[3] == 0 )&&(v[4] == 0 )&&(v[5] == 0 )) op = -1;
else if((v[1] == 1 )&&(v[2] == 1 )&&(v[3] == 0 )&&(v[4] == 0 )&&(v[5] == 0 )) op = -1;
else if((v[1] == 0 )&&(v[2] == 1 )&&(v[3] == 0 )&&(v[4] == 0 )&&(v[5] == 0 )) op = -1;
else if((v[1] == 0 )&&(v[2] == 1 )&&(v[3] == 1 )&&(v[4] == 0 )&&(v[5] == 0 )) op = -1;
else if((v[1] == 1 )&&(v[2] == 1 )&&(v[3] == 1 )&&(v[4] == 0 )&&(v[5] == 0 )) op = -1;

else if((v[1] == 0 )&&(v[2] == 0 )&&(v[3] == 1 )&&(v[4] == 0 )&&(v[5] == 0 )) op =  0;

else if((v[1] == 0 )&&(v[2] == 0 )&&(v[3] == 1 )&&(v[4] == 1 )&&(v[5] == 1 )) op =  1;
else if((v[1] == 0 )&&(v[2] == 0 )&&(v[3] == 1 )&&(v[4] == 1 )&&(v[5] == 0 )) op =  1;
else if((v[1] == 0 )&&(v[2] == 0 )&&(v[3] == 0 )&&(v[4] == 1 )&&(v[5] == 0 )) op =  1;
else if((v[1] == 0 )&&(v[2] == 0 )&&(v[3] == 0 )&&(v[4] == 1 )&&(v[5] == 1 )) op =  1;
else if((v[1] == 0 )&&(v[2] == 0 )&&(v[3] == 0 )&&(v[4] == 0 )&&(v[5] == 1 )) op =  1;

else if((v[1] == 0 )&&(v[2] == 0 )&&(v[3] == 0 )&&(v[4] == 0 )&&(v[5] == 0 )) op =  2;


  return op;
}
