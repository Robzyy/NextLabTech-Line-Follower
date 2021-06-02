class Motor
{
private:
    const int m_enablePin, m_input1, m_input2;
public:
    Motor(int enablePin, int input1, int input2)
        : m_enablePin{enablePin}, m_input1{input1}, m_input2{input2}
    {
        pinMode(enablePin, OUTPUT);
        pinMode(input1, OUTPUT);
        pinMode(input2, OUTPUT);
    }

    void drive(int speed)
    {
        if(speed != 0)
        {
            if(speed > 0)
            {
                digitalWrite(m_input1, HIGH);
                digitalWrite(m_input2, LOW);
                analogWrite(m_enablePin, speed);
            }
            else
            {
                digitalWrite(m_input1, LOW);
                digitalWrite(m_input2, HIGH);
                analogWrite(m_enablePin, -speed);
            }
        }
        else
        {
            digitalWrite(m_input1, LOW);
            digitalWrite(m_input2, LOW);
            analogWrite(m_enablePin, 0);
        }
    }
};

Motor left{5, 8, 9};
Motor right{6, 10, 11};

class Sensors{
private:
    const int m_pin;
    int m_value{};

public:
    Sensors(const int pin) 
        :m_pin{pin}
    {
        pinMode(pin, INPUT);
    }

    void read()
    {
        m_value = digitalRead(m_pin);
        // LED turned off means read value is 0
        // LED turned on  means read value is 1
    }

    void print()
    {
        Serial.print(m_value);
        Serial.print(' ');        
    }
};

Sensors sensor[]{ {2}, {3}, {4}, {7}, {12} };


void setup()
{
    Serial.begin(9600);
}

void loop()
{
    for(auto& i: sensor)
    {
        i.read();
        // i.print();
    }
    // Serial.println();
}
