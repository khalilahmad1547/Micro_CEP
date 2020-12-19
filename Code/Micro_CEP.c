// Enable Pins of H-Bridge
#define Enable_Pin_One LatC.F1  // EN1 connected with PortC.1
#define Enable_Pin_Two LatC.F2  // EN2 connected with PortC.2

// Input Pins of H-Bridge
#define Input_Pin_One LatD.F0       // IN1 connected to PortD.0
#define Input_Pin_Two LatD.F1       // IN2 connected to PortD.1
#define Input_Pin_Three LatD.F2     // IN3 connected to PortD.2
#define Input_Pin_Four LatD.F3      // IN4 connected to PortD.3

// Sensers Pins


void main() {
     TrisD = 0;                 // making D port OUTPUT
     TrisC = 0;                 // Making C port OUTPUT
     Input_Pin_One = 0;
     Input_Pin_Two = 1;
     Input_Pin_Three = 0;
     Input_Pin_Four = 1;
     Enable_Pin_One = 1;
     Enable_Pin_Two = 1;
     while(1)
     {

     }
}