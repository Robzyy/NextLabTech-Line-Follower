/*
*
*
*   This is a Romanian x English fiasco... it happens 
*
*
*/
//Enable(s) for motors
#define enA 5
#define enB 6

//Motor pins
#define in1 8
#define in2 9

#define in3 10
#define in4 11

//Sensor pins
#define sens1 2
#define sens2 3
#define sens3 4
#define sens4 7
#define sens5 12

int speed1 = 155, speed2 = 50;
int lastCurve;

void setup()
{
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

void loop()
{
    int v[6]{};
    readSens(v);
    setDirection(determineDirection(v));

    //printSensors(v);
}

void setDirection(int x)
{
    //Serial.println("debug test");
    switch (x)
    {
    case -1:
        goLeft();
        lastCurve = -1;
        //Serial.println("case -1");
        break;
    case 0:
        goForward();
        //Serial.println("case  0");
        break;
    case 1:
        goRight();
        lastCurve = 1;
        //Serial.println("case  1");
        break;
    default:
        //Serial.println("case default");
        setDirection(lastCurve);
    }
}

void readSens(int v[6])
{
    v[1] = !digitalRead(sens1);
    v[2] = !digitalRead(sens2);
    v[3] = !digitalRead(sens3);
    v[4] = !digitalRead(sens4);
    v[5] = !digitalRead(sens5);
}

void goForward()
{
    //Motor left
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, speed1);
    //Motor right
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, speed1);
}

void goLeft()
{
    //Motor left
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, speed2);
    //Motor right
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, speed1);
}

void goRight()
{
    //Motor left
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, speed1);
    //Motor right
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, speed2);
}

void goBackwards()
{
    //Motor left
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, speed1);
    //Motor right
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, speed1);
}

void printSensors(int v[6])
{
    for (int i = 1; i <= 5; i++)
    {
        Serial.print(v[i]);
        Serial.print(" ");
    }
    Serial.println();
}

int determineDirection(int v[6])
{
    int op; //operation
    if ((v[1] == 1) && (v[2] == 0) && (v[3] == 0) && (v[4] == 0) && (v[5] == 0))
        op = -1;
    else if ((v[1] == 1) && (v[2] == 1) && (v[3] == 0) && (v[4] == 0) && (v[5] == 0))
        op = -1;
    else if ((v[1] == 0) && (v[2] == 1) && (v[3] == 0) && (v[4] == 0) && (v[5] == 0))
        op = -1;
    else if ((v[1] == 0) && (v[2] == 1) && (v[3] == 1) && (v[4] == 0) && (v[5] == 0))
        op = -1;
    else if ((v[1] == 1) && (v[2] == 1) && (v[3] == 1) && (v[4] == 0) && (v[5] == 0))
        op = -1;

    else if ((v[1] == 0) && (v[2] == 0) && (v[3] == 1) && (v[4] == 0) && (v[5] == 0))
        op = 0;

    else if ((v[1] == 0) && (v[2] == 0) && (v[3] == 1) && (v[4] == 1) && (v[5] == 1))
        op = 1;
    else if ((v[1] == 0) && (v[2] == 0) && (v[3] == 1) && (v[4] == 1) && (v[5] == 0))
        op = 1;
    else if ((v[1] == 0) && (v[2] == 0) && (v[3] == 0) && (v[4] == 1) && (v[5] == 0))
        op = 1;
    else if ((v[1] == 0) && (v[2] == 0) && (v[3] == 0) && (v[4] == 1) && (v[5] == 1))
        op = 1;
    else if ((v[1] == 0) && (v[2] == 0) && (v[3] == 0) && (v[4] == 0) && (v[5] == 1))
        op = 1;

    else if ((v[1] == 0) && (v[2] == 0) && (v[3] == 0) && (v[4] == 0) && (v[5] == 0))
        op = 2;

    //Serial.println(op);
    return op;
}
