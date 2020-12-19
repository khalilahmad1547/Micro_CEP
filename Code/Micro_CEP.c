// Enable Pins of H-Bridge
#define Enable_Pin_One LatC.F1      // EN1 connected with PortC.1
#define Enable_Pin_Two LatC.F2      // EN2 connected with PortC.2

// Input Pins of H-Bridge
// For 1st Motor
#define Input_Pin_One LatD.F0       // IN1 connected to PortD.0
#define Input_Pin_Two LatD.F1       // IN2 connected to PortD.1
// For 2nd Motor
#define Input_Pin_Three LatD.F2     // IN3 connected to PortD.2
#define Input_Pin_Four LatD.F3      // IN4 connected to PortD.3

// Sensers Pins
#define Senser_One PortB.F0
#define Senser_Right PortB.F1        // Left Senser
#define Senser_Three PortB.F2
#define Senser_Head PortB.F3        // Head Sense
#define Senser_Five PortB.F4
#define Senser_Left PortB.F5       // Right Senser

// Snesers default Ouput Value
#define is_Line    1
#define not_Line   0

// Motor controlling Functions
void Motor_Left_Stop();
void Motor_Left_Start();

void Motor_Right_Stop();
void Motor_Right_Start();

void main() {
     TrisD = 0;                     // making D port OUTPUT
     TrisC = 0;                     // Making C port OUTPUT
     
     TrisB = 0xff;                  // Making Port B INPUT
     // by default running staraight
     Input_Pin_One = 0;
     Input_Pin_Two = 1;
     Input_Pin_Three = 0;
     Input_Pin_Four = 1;
     Enable_Pin_One = 1;
     Enable_Pin_Two = 1;
     while(1)
     {
             if(Senser_Head == not_Line)
             {
                  if(Senser_Left == not_Line && Senser_Right == not_Line)
                     {
                          // Dead END here
                          Motor_Left_Stop();
                          Motor_Right_Start();
                     }
                  else if (Senser_Left == is_Line && Senser_Right == not_Line)
                      {
                          // Turn Left
                          Motor_Left_Stop();
                          Motor_Right_Start();
                      }
                  else if (Senser_Left == not_Line && Senser_Right == is_Line)
                       {
                          // Turn Right
                          Motor_Left_Start();
                          Motor_Right_Stop();
                       }
                  else if (Senser_Left == is_Line && Senser_Right == is_Line)
                       {
                          // Turn Right
                          Motor_Left_Start();
                          Motor_Right_Stop();
                       }
             }
             else
             {
              Motor_Left_Start();
              Motor_Right_Start();
             }
     }
}

// Function Definations
void Motor_Right_Stop()
{
    Input_Pin_One = 0;
    Input_Pin_Two = 0;
}

void Motor_Right_Start()
{
    Input_Pin_One = 1;
    Input_Pin_Two = 0;
}

void Motor_Left_Stop()
{
    Input_Pin_Three = 0;
    Input_Pin_Four = 0;
}

void Motor_Left_Start()
{
    Input_Pin_Three = 1;
    Input_Pin_Four = 0;
}