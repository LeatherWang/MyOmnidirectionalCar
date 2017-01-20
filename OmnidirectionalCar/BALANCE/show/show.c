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
void APP_Show(void)
{    
	  int app_2,app_3,app_4;
	  app_4=(Voltage-1110)*2/3;	
  	if(app_4<0)app_4=1;
	  if(app_4==0)app_4=31;
	  if(app_4>100)app_4=100;   //�Ե�ѹ���ݽ��д���
	  if(Run_Flag==0)
		{		
			app_2=Move_X*0.7; if(app_2<0)app_2=-app_2;			                   //�Ա��������ݾ������ݴ�������ͼ�λ�
			app_3=Move_Y*0.7;  if(app_3<0)app_3=-app_3;
			printf("Z%d:%d:%d:%dL$",(u8)app_2,(u8)app_3,(u8)app_4,(int)Move_Z);//��ӡ��APP����
		}
		else
		{
			
			printf("Z%d:%d:%d:%dL$",0,0,(u8)app_4,0);//��ӡ��APP����
		}
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
		DataScope_Get_Channel_Data( Target_A, 1 );       //��ʾ�Ƕ� ��λ���ȣ��㣩
		DataScope_Get_Channel_Data(Encoder_A, 2 );         //��ʾ�����������ľ��� ��λ��CM 
		DataScope_Get_Channel_Data(Target_B, 3 );                 //��ʾ��ص�ѹ ��λ��V
  	DataScope_Get_Channel_Data(Encoder_B, 4 );     
		DataScope_Get_Channel_Data(Target_C, 5 ); //����Ҫ��ʾ�������滻0������
		DataScope_Get_Channel_Data(Encoder_C , 6 );//����Ҫ��ʾ�������滻0������
	}
else
	{
		DataScope_Get_Channel_Data( Target_A, 1 );       //��ʾ�Ƕ� ��λ���ȣ��㣩
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