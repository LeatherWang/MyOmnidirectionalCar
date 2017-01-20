#include "show.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���
float Vol;
/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
void oled_show(void)
{
	  //=============�ڶ�����ʾ�¶Ⱥ;���===============//	
  	OLED_ShowString(0,0,"X:");
		if(Pitch<0)		OLED_ShowNumber(15,0,Pitch+360,3,12);
		else					OLED_ShowNumber(15,0,Pitch,3,12);	
       
  	OLED_ShowString(40,0,"Y:");
		if(Roll<0)		OLED_ShowNumber(55,0,Roll+360,3,12);
		else					OLED_ShowNumber(55,0,Roll,3,12);	
	
	   OLED_ShowString(80,0,"Z:");
		if(Yaw<0)		OLED_ShowNumber(95,0,Yaw+360,3,12);
		else					OLED_ShowNumber(95,0,Yaw,3,12);		
	  //=============�ڶ�����ʾ�¶Ⱥ;���===============//	
			                    OLED_ShowString(00,10,"GZ");
		if( gyro[2]<0)      	OLED_ShowString(20,10,"-"),
		                      OLED_ShowNumber(30,10,-gyro[2],5,12);
		else                 	OLED_ShowString(20,10,"+"),
		                      OLED_ShowNumber(30,10, gyro[2],5,12);			
		
					                OLED_ShowString(70,10,"V");
		if( RC_Velocity<0)	  OLED_ShowString(80,10,"-"),
		                      OLED_ShowNumber(90,10,-RC_Velocity,5,12);
		else                 	OLED_ShowString(80,10,"+"),
		                      OLED_ShowNumber(90,10, RC_Velocity,5,12);	
  if(Run_Flag==0)
  {		
		//=============��������ʾ������1=======================//	
		  if( Target_A<0)		  OLED_ShowString(00,20,"-"),
		                      OLED_ShowNumber(15,20,-Target_A,5,12);
		else                 	OLED_ShowString(0,20,"+"),
		                      OLED_ShowNumber(15,20, Target_A,5,12); 
		
		if( Encoder_A<0)		OLED_ShowString(80,20,"-"),
		                      OLED_ShowNumber(95,20,-Encoder_A,4,12);
		else                 	OLED_ShowString(80,20,"+"),
		                      OLED_ShowNumber(95,20, Encoder_A,4,12);
 		//=============��������ʾ������1=======================//	
		  if( Target_B<0)		OLED_ShowString(00,30,"-"),
		                      OLED_ShowNumber(15,30,-Target_B,5,12);
		else                 	OLED_ShowString(0,30,"+"),
		                      OLED_ShowNumber(15,30, Target_B,5,12); 
		
		if( Encoder_B<0)		OLED_ShowString(80,30,"-"),
		                      OLED_ShowNumber(95,30,-Encoder_B,4,12);
		else                 	OLED_ShowString(80,30,"+"),
		                      OLED_ShowNumber(95,30, Encoder_B,4,12);	
		//=============��������ʾ������1=======================//	
		  if( Target_C<0)		OLED_ShowString(00,40,"-"),
		                      OLED_ShowNumber(15,40,-Target_C,5,12);
		else                 	OLED_ShowString(0,40,"+"),
		                      OLED_ShowNumber(15,40, Target_C,5,12); 
		
		if( Encoder_C<0)		OLED_ShowString(80,40,"-"),
		                      OLED_ShowNumber(95,40,-Encoder_C,4,12);
		else                 	OLED_ShowString(80,40,"+"),
		                      OLED_ShowNumber(95,40, Encoder_C,4,12);
	}
	else if(Run_Flag==1)
  {		
		//=============��������ʾ������1=======================//	
		  if( Target_A<0)		  OLED_ShowString(00,20,"-"),
		                      OLED_ShowNumber(15,20,-Target_A,5,12);
		else                 	OLED_ShowString(0,20,"+"),
		                      OLED_ShowNumber(15,20, Target_A,5,12); 
		
		if( Position_A<0)		  OLED_ShowString(80,20,"-"),
		                      OLED_ShowNumber(95,20,-Position_A,5,12);
		else                 	OLED_ShowString(80,20,"+"),
		                      OLED_ShowNumber(95,20, Position_A,5,12);
 		//=============��������ʾ������1=======================//	
		  if( Target_B<0)		OLED_ShowString(00,30,"-"),
		                      OLED_ShowNumber(15,30,-Target_B,5,12);
		else                 	OLED_ShowString(0,30,"+"),
		                      OLED_ShowNumber(15,30, Target_B,5,12); 
		
		if( Position_B<0)		OLED_ShowString(80,30,"-"),
		                      OLED_ShowNumber(95,30,-Position_B,5,12);
		else                 	OLED_ShowString(80,30,"+"),
		                      OLED_ShowNumber(95,30, Position_B,5,12);	
		//=============��������ʾ������1=======================//	
		  if( Target_C<0)		OLED_ShowString(00,40,"-"),
		                      OLED_ShowNumber(15,40,-Target_C,5,12);
		else                 	OLED_ShowString(0,40,"+"),
		                      OLED_ShowNumber(15,40, Target_C,5,12); 
		
		if( Position_C<0)		OLED_ShowString(80,40,"-"),
		                      OLED_ShowNumber(95,40,-Position_C,5,12);
		else                 	OLED_ShowString(80,40,"+"),
		                      OLED_ShowNumber(95,40, Position_C,5,12);
	}
		//=============��������ʾ��ѹ=======================//
		if(Run_Flag==0)       OLED_ShowString(00,50,"VELOCITY");
	else	if(Run_Flag==1)   OLED_ShowString(00,50,"POSITION");
		                      OLED_ShowString(88,50,".");
		                      OLED_ShowString(110,50,"V");
		                      OLED_ShowNumber(75,50,Voltage/100,2,12);
		                      OLED_ShowNumber(98,50,Voltage%100,2,12);
		 if(Voltage%100<10) 	OLED_ShowNumber(92,50,0,2,12);
//		//=============��������ʾ�Ƕ�=======================//
//		                      OLED_ShowString(0,50,"Angle");
//		if(Angle_Balance<0)		OLED_ShowNumber(45,50,Angle_Balance+360,3,12);
//		else					        OLED_ShowNumber(45,50,Angle_Balance,3,12);
		//=============ˢ��=======================//
		OLED_Refresh_Gram();	
	}
/**************************************************************************
�������ܣ���APP��������
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
typedef union
{
    unsigned int sum;//int = qint32
    u8 son[2];
} MyUnion;
MyUnion Union_dataBuf;
u8 data_to_send[50];				//�������ݻ�����
unsigned int Position_X,Position_Y;
#define A_PARAMETER 0.5
#define B_PARAMETER (2/sqrt(3.0))

void APP_Show(void)
{   
		u8 _cnt=0;
    u8 i=0;
    u8 sum = 0;
		Position_X = (unsigned int)(Position_A/20.0f+350);//�˶�ѧ��ģ->����
    Position_Y = (unsigned int)(((A_PARAMETER*Position_A + Position_B)*B_PARAMETER)/20.0 +350);

    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAF;
    data_to_send[_cnt++]=0x01;//flag
    data_to_send[_cnt++]=0;
	
		Union_dataBuf.sum = Position_X;
    data_to_send[_cnt++]=Union_dataBuf.son[1];
    data_to_send[_cnt++]=Union_dataBuf.son[0];
	
		Union_dataBuf.sum = Position_Y;
    data_to_send[_cnt++]=Union_dataBuf.son[1];
    data_to_send[_cnt++]=Union_dataBuf.son[0];

    data_to_send[3] = _cnt-4;

     for(i=0;i<_cnt;i++)
        sum += data_to_send[i];

    data_to_send[_cnt++]=sum;
		
		ANO_UART3_Put_Buf(data_to_send, _cnt);
}
/**************************************************************************
�������ܣ�����ʾ��������λ���������� �ر���ʾ��
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void DataScope(void)
{   
	if(Run_Flag==0)
	{
		DataScope_Get_Channel_Data(Target_A, 1 );       //��ʾ�Ƕ� ��λ���ȣ��㣩
		DataScope_Get_Channel_Data(Encoder_A, 2 );         //��ʾ�����������ľ��� ��λ��CM 
		DataScope_Get_Channel_Data(Target_B, 3 );                 //��ʾ��ص�ѹ ��λ��V
  	DataScope_Get_Channel_Data(Encoder_B, 4 );     
		DataScope_Get_Channel_Data(Target_C, 5 ); //����Ҫ��ʾ�������滻0������
		DataScope_Get_Channel_Data(Encoder_C , 6 );//����Ҫ��ʾ�������滻0������
	}
else
	{
		DataScope_Get_Channel_Data(Target_A, 1 );       //��ʾ�Ƕ� ��λ���ȣ��㣩
		DataScope_Get_Channel_Data(Position_A, 2 );         //��ʾ�����������ľ��� ��λ��CM 
		DataScope_Get_Channel_Data(Target_B, 3 );                 //��ʾ��ص�ѹ ��λ��V
  	DataScope_Get_Channel_Data(Position_B, 4 );     
		DataScope_Get_Channel_Data(Target_C, 5 ); //����Ҫ��ʾ�������滻0������
		DataScope_Get_Channel_Data(Position_C , 6 );//����Ҫ��ʾ�������滻0������
	}
//		DataScope_Get_Channel_Data(0, 7 );
//		DataScope_Get_Channel_Data( 0, 8 ); 
//		DataScope_Get_Channel_Data(0, 9 );  
//		DataScope_Get_Channel_Data( 0 , 10);
		Send_Count = DataScope_Data_Generate(6);
		for( i = 0 ; i < Send_Count; i++) 
		{
		while((USART2->SR&0X40)==0);  
		USART2->DR = DataScope_OutPut_Buffer[i]; 
		}
}
