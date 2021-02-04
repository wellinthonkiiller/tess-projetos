#define BT_GATE_OPEN 7
#define BT_GATE_CLOSE 6
#define SENSOR_GATE_OPEN 8
#define SENSOR_GATE_CLOSED 9
#define SENSOR_IR 10

typedef enum
{
  IDLE_STATE,
  GATE_OPENING,
  GATE_CLOSING  
}MachineStates;

int stateMachine = IDLE_STATE;

void openGate()
{
  if (digitalRead(SENSOR_GATE_OPEN) == 0) //Limit switch sensor activated
    {
        Serial.println("The gate is open");
        stateMachine = IDLE_STATE;
    }
    else if (digitalRead(BT_GATE_CLOSE) == 0) //Button close pressed
        stateMachine = IDLE_STATE;
}

void closeGate()
{
    if (digitalRead(SENSOR_IR) == 0) //Infrared sensor activated
    {
        Serial.println("The gate was interrupted");
        stateMachine = GATE_OPENING;
    }
    else if (digitalRead(SENSOR_GATE_CLOSED) == 0) //Limit switch sensor activated
    {
        Serial.println("The gate is closed");               
      stateMachine = IDLE_STATE;
    }
    else if (digitalRead(BT_GATE_OPEN) == 0) //Button open pressed
        stateMachine = GATE_OPENING;           
}

//Idle state
void state0()
{
  if (digitalRead(BT_GATE_OPEN) == 0) //Button open pressed
      stateMachine = GATE_OPENING;
    else if (digitalRead(BT_GATE_CLOSE) == 0) //Button close pressed
      stateMachine = GATE_CLOSING;
}

//Opening state
void state1()
{
  Serial.println("The gate is opening");
    openGate();
}

//Closing state
void state2()
{
    Serial.println("The gate is closing");
    closeGate();
}

void setup()
{
  Serial.begin(9600);
  
    //Configure inputs/outputs
    pinMode(BT_GATE_OPEN, INPUT);
    pinMode(BT_GATE_CLOSE, INPUT);
    pinMode(SENSOR_GATE_OPEN, INPUT);
    pinMode(SENSOR_GATE_CLOSED, INPUT);
    pinMode(SENSOR_IR, INPUT); 
}

void loop()
{  
    switch (stateMachine)
    {
        case IDLE_STATE:
            state0();                                   
            break;
        case GATE_OPENING:
            state1();      
            break;
        case GATE_CLOSING:
            state2();
            break;
    }
}
