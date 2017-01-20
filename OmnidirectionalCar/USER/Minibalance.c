#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/ 
u8 Flag_Left,Flag_Right,Flag_Direction=0;   //����ң����صı���
u8 Flag_Stop=1,Flag_Show=0;                 //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_A,Encoder_B,Encoder_C;          //���������������
long int Position_A,Position_B,Position_C,Rate_A,Rate_B,Rate_C; //PID������ر���
int Encoder_A_EXTI;     //ͨ���ⲿ�ж϶�ȡ�ı���������                       
long int Motor_A,Motor_B,Motor_C;      //���PWM����
long int Target_A,Target_B,Target_C;    //���Ŀ��ֵ
int Voltage;                              //��ص�ѹ������صı���
float Show_Data_Mb;                         //ȫ����ʾ������������ʾ��Ҫ�鿴������                         
u8 delay_50,delay_flag;                //��ʱ��ر���
int RC_Velocity=30,RC_Position=3000,RCX_Position,RCY_Position,RCZ_Position;   //����ң�ص��ٶȺ�λ��ֵ
u8 Usart3_Receive,Left_Receive,Right_Receive,Run_Flag=0;  //����ң����ر���������״̬��־λ
u8 rxbuf[8],Urxbuf[8],CAN_ON_Flag=0,Usart_ON_Flag=0,Usart_Flag;  //CAN�ʹ��ڿ�����ر���
u8 txbuf[8],txbuf2[8];                       //CAN������ر���
float Pitch,Roll,Yaw,Move_X,Move_Y,Move_Z;   //����ǶȺ�XYZ��Ŀ���ٶ�
int main(void)
{ 
	Stm32_Clock_Init(9);            //=====ϵͳʱ������
	delay_init(72);                 //=====��ʱ��ʼ��
	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
	LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	KEY_Init();                     //=====������ʼ��
	if(MODE==0)Run_Flag=1;           //=====�����Ĺ����У��û����������£����ɽ���λ��Ĭ��
	else Run_Flag=0;                //=====�������Ĭ�ϵ��ٶ�ģʽ
	OLED_Init();                    //=====OLED��ʼ��
	uart2_init(36,128000);          //=====����2��ʼ��
  uart3_init(36,115200);            //=====����3��ʼ��
	Encoder_Init_TIM2();            //=====�������ӿ�
	Encoder_Init_TIM3();            //=====�������ӿ�
	Encoder_Init_TIM4();            //=====��ʼ��������C
	Adc_Init();                     //=====adc��ʼ��
	IIC_Init();                     //=====IIC��ʼ��
  MPU6050_initialize();           //=====MPU6050��ʼ��	
  DMP_Init();                     //=====��ʼ��DMP     
	MiniBalance_PWM_Init(7199,0);   //=====��ʼ��PWM 10KHZ�������������
  EXTI_Init();                    //=====MPU6050 5ms��ʱ�жϳ�ʼ��
  CAN1_Mode_Init(1,2,3,6,0);      //=====CAN��ʼ��
	while(1)
		{	
			BUZZER=0;                 //�رշ�����
	    if(Flag_Show==0)          //ʹ��MiniBalanceV3.5 APP��OLED��ʾ��
			{
				//APP_Show();	
				oled_show();          //===��ʾ����
	    }
    	else                      //ʹ��MiniBalanceV3.5��λ�� ��λ��ʹ�õ�ʱ����Ҫ�ϸ��ʱ�򣬹ʴ�ʱ�ر�app��ز��ֺ�OLED��ʾ��
  		{
				DataScope();          //����MiniBalanceV3.5��λ��
			}
			delay_flag=1;	
			delay_50=0;
			while(delay_flag);	     //ͨ��MPU6050��INT�ж�ʵ�ֵ�50ms��׼��ʱ				
		} 
}