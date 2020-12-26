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
#define no_Line   0

// Status LED
#define Status_LED LatD.F6

// Button
/*
 This button be used to start following optimized path
 */
#define follow PortB.F7

// Motor controlling Functions
void Motor_Left_Stop();
void Motor_Left_Start();

void Motor_Right_Stop();
void Motor_Right_Start();

// For implementing maze solving

/****** All th Golbel variables****/
/* 
 "address" A globel address for EEPROM it will
 Be pointing to the last occupide space in EEPROM
*/
int address = 0;
/*
 "last_written"
 is just a varibale to store the last written so we may not
 write it again
 It would be a unique number for all the checks below in "void main()"
*/
int last_written = -1;
/*
"dead_end" is used as a flag to remember that a dead end is
encountered or not
dead_end == 1 => dead end encountered
dead_end == 0 => No dead end encountered
*/
int dead_end = 0;

/****** All th functions for path optimization ****/
void buildPath(char my_turn, int uniq_num);

void main() {
     // All the main varibales
     // For following optimized path
     char dir_to_take;

     // All the pin configurations
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
      if(Senser_Head == no_Line && Senser_Right == no_Line && Senser_Left == no_Line)
      {
       // Dead End Occured
       // Take 360* turn
       Motor_Right_Start();
       Motor_Left_Stop();
       
       // For Maze solving
       buildPath('B', 0);
       
       // Rasing Dead end flag
       dead_end = 1;
      
      }
      else if(Senser_Head == no_Line && Senser_Right == no_Line && Senser_Left == is_Line)
      {
       // Only Left Path exist
       // Take a Left turn
       Motor_Right_Start();
       Motor_Left_Stop();
       
       // For Maze solving
       buildPath('L', 1);
      
      }
      else if(Senser_Head == no_Line && Senser_Right == is_Line && Senser_Left == no_Line)
      {
       // Only Right path exist
       // Turn Right
       Motor_Right_Stop();
       Motor_Left_Start();
       
       // For Maze solving
       buildPath('R', 2);

      }
      else if(Senser_Head == no_Line && Senser_Right == is_Line && Senser_Left == is_Line)
      {
       // Right & left Path exist
       // Turn Right
       Motor_Right_Stop();
       Motor_Left_Start();
       
       // For Maze solving
       buildPath('R', 3);

      }
      else if(Senser_Head == is_Line && Senser_Right == no_Line && Senser_Left == no_Line)
      {
       // Only straght path exist
       // Go Straight
       Motor_Right_Start();
       Motor_Left_Start();
       
       // For Maze solving
       // 'N' is for not storing
       buildPath('N', 4);

      }
      else if(Senser_Head == is_Line && Senser_Right == no_Line && Senser_Left == is_Line)
      {
       // Stright & Left Path exist
       // Go Stright
       Motor_Right_Start();
       Motor_Left_Start();
       
       // For Maze solving
       buildPath('S', 5);

      }
      else if(Senser_Head == is_Line && Senser_Right == is_Line && Senser_Left == no_Line)
      {
       // Stright & Right Path exist
       // Go Right
       Motor_Right_Stop();
       Motor_Left_Start();
       
       // For Maze solving
       buildPath('R', 6);

      }
      else if(Senser_Head == is_Line && Senser_Right == is_Line && Senser_Left == is_Line)
      {
       // All stright, Right & left path exist
       // Go Right
       Motor_Right_Stop();
       Motor_Left_Start();
       
       // For Maze solving
       buildPath('R', 7);
       // For detecting Maze END
       delay_ms(5000);
       if(Senser_Head == is_Line && Senser_Right == is_Line && Senser_Left == is_Line)
       {
        Motor_Right_Stop();
        Motor_Left_Stop();
        break;
       }

      }
     }
     
     // blinking and waiting for the switch to turn on
     while(follow != 1)      // Not pressed
     {
      Status_LED = ~Status_LED;
      delay_ms(500);
      Status_LED = ~Status_LED;
      delay_ms(500);
     }
     
     // Following the Optimized Path
     address = 0;               // re-initilizing address pointer
     
     while(1)
     {
      if(Senser_Head == is_Line && Senser_Right == no_Line && Senser_Left == no_Line)
      {
       // Only straght path exist
       // A normal Path
       
       // Go Straight
       Motor_Right_Start();
       Motor_Left_Start();
      }
      else
      {
       // Any turn is detected
       // Have to take a right turn as determined by optimization
       
       dir_to_take = EEPROM_Read(address);
       if(dir_to_take == 'R')
       {
        // Go Right
        Motor_Right_Stop();
        Motor_Left_Start();
       }
       else if(dir_to_take == 'L')
       {
        // Go Left
        Motor_Right_Start();
        Motor_Left_Stop();
       }
       else if(dir_to_take == 'S')
       {
        // Go Stright
        Motor_Right_Start();
        Motor_Left_Start();
       }
       else if(dir_to_take == 'N')
       {
        // End of the Maze
        
        // Stop here
        Motor_Right_Stop();
        Motor_Left_Stop();
        // getting out of loop
        break;
       }
       
       // updating addreaa
       address = address + 1;
      }
     }

     // End signal
     while(1)
     {
      Status_LED = 1;
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

void buildPath(char my_turn, int uniq_num)
{
     if(last_written != uniq_num)
     {
      if(my_turn != 'N')
      {
       // Stil have to write path
       EEPROM_Write(address, my_turn);
       address = address + 1;
      }
       // Updating Last turn status
       last_written = uniq_num;
     }
     // PATH optimization
     if(dead_end == 1)
     {
       // Optimizing Path
       char s_last_turn = EEPROM_Read(address - 3);
       char last_turn =  EEPROM_Read(address - 1);
       
       if(s_last_turn == 'R' && last_turn == 'L')
       {
           // PATH is RBL & optimized as  B
           EEPROM_Write(address - 3, 'B');
           address = address - 2;       // Updating address
       }
       else if(s_last_turn == 'R' && last_turn == 'R')
       {
           // PATH is LBL & optimized as  S
           EEPROM_Write(address - 3, 'S');
           address = address - 2;       // Updating address
       }
       else if(s_last_turn == 'L' && last_turn == 'L')
       {
           // PATH is LBL & optimized as  S
           EEPROM_Write(address - 3, 'S');
           address = address - 2;       // Updating address
       }
       else if(s_last_turn == 'L' && last_turn == 'R')
       {
           // PATH is LBR & optimized as  B
           EEPROM_Write(address - 3, 'B');
           address = address - 2;       // Updating address
       }
       else if(s_last_turn == 'S' && last_turn == 'L')
       {
           // PATH is SBL & optimized as  S
           EEPROM_Write(address - 3, 'R');
           address = address - 2;       // Updating address
       }
       else if(s_last_turn == 'S' && last_turn == 'S')
       {
           // PATH is SBS & optimized as  S
           EEPROM_Write(address - 3, 'B');
           address = address - 2;       // Updating address
       }
       else if(s_last_turn == 'L' && last_turn == 'S')
       {
           // PATH is LBS & optimized as  R
           EEPROM_Write(address - 3, 'R');
           address = address - 2;       // Updating address
       }
       
       // Updating "dead_end" Flag
       if(EEPROM_Read(address - 1) != 'B')
       {
         dead_end = 0;
       }
     }
}