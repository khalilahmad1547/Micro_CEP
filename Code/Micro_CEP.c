
void main() {
     TrisD = 0;
     LatD = 0b00000101;
     PWM1_Init(10000);
     PWM1_Set_Duty(255);
     PWM1_Start();
     PWM2_Init(10000);
     PWM2_Set_Duty(255);
     PWM2_Start();
     while(1)
     {
     }
}