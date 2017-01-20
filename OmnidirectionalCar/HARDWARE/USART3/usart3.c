
#include "usart3.h"

 u8 mode_data[2];
 u8 six_data_stop[2]={0X59,0X59};  //ֹͣ��������
 u8 six_data_start[2]={0X58,0X58};  //������������

/**************************************************************************
�������ܣ�����3��ʼ��
��ڲ�����pclk2:PCLK2 ʱ��Ƶ��(Mhz)    bound:������
����  ֵ����
**************************************************************************/
void uart3_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<3;   //ʹ��PORTB��ʱ��  
	RCC->APB1ENR|=1<<18;  //ʹ�ܴ���ʱ�� 
	GPIOB->CRH&=0XFFFF00FF; 
	GPIOB->CRH|=0X00008B00;//IO״̬����
	GPIOB->ODR|=1<<10;	  
	RCC->APB1RSTR|=1<<18;   //��λ����1
	RCC->APB1RSTR&=~(1<<18);//ֹͣ��λ	   	   
	//����������
 	USART3->BRR=mantissa; // ����������	 
	USART3->CR1|=0X200C;  //1λֹͣ,��У��λ.
	//ʹ�ܽ����ж�
	USART3->CR1|=1<<8;    //PE�ж�ʹ��
	USART3->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(0,0,USART3_IRQn,2);//��2��������ȼ� 
}

/**************************************************************************
�������ܣ�����3�����ж�
��ڲ�������
����  ֵ����
**************************************************************************/
static u8 RxState = 0;
static u8 RxBuffer[256];
int USART3_IRQHandler(void)
{	
	if(USART3->SR&(1<<5))//���յ�����
	{	
		u8 com_data=USART3->DR;
		static u8 _data_len = 0,_data_cnt = 0;
		if(RxState==0&&com_data==0xAA)
		{
			RxState=1;
			RxBuffer[0]=com_data;
		}
		else if(RxState==1&&com_data==0xAF)
		{
			RxState=2;
			RxBuffer[1]=com_data;
		}
		else if(RxState==2&&com_data<=0XF1)
		{ 
			RxState=3;
			RxBuffer[2]=com_data;
		}
		else if(RxState==3&&com_data<255)
		{
			RxState = 4;
			RxBuffer[3]=com_data;
			_data_len = com_data;
			_data_cnt = 0;
		}
		else if(RxState==4&&_data_len>0)
		{
			_data_len--;
			RxBuffer[4+_data_cnt++]=com_data;
			if(_data_len==0)
				RxState = 5;
		}
		else if(RxState==5)
		{
			RxState = 0;
			RxBuffer[4+_data_cnt]=com_data;
			ANO_DT_Data_Receive_Anl(RxBuffer,_data_cnt+5);
		}
		else
			RxState = 0;
	}  	
return 0;	
} 

void ANO_DT_Data_Receive_Anl(u8 *data_buf,u8 num)
{
	u8 sum = 0,i=0;
	for(i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;		
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		return;		

	if(*(data_buf+2)==0X01)								
  {
     RCX_Position = ( ((vs16)(*(data_buf+4)<<8)|*(data_buf+5))  -350)*20;
     RCY_Position = ( ((vs16)(*(data_buf+6)<<8)|*(data_buf+7))  -350)*20;
    // RCZ_Position = ( (vs16)(*(data_buf+8)<<8)|*(data_buf+9) );
  }
}

/**************************************************************************
�������ܣ�����ɨ��
**************************************************************************/
u8 click_RC (void)
{
			static u8 flag_key=1;//�������ɿ���־
	    u8 temp;
			if(flag_key&&Usart3_Receive!=0x5A)
			{
			flag_key=0;
		  if(Usart3_Receive>=0x01&&Usart3_Receive<=0x08)temp=Usart3_Receive;
		  else	if(Usart3_Receive>=0x41&&Usart3_Receive<=0x48)temp=Usart3_Receive-0x40;	
		//	else 	temp=0;
			return temp;	// ��������
			}
			else if(Usart3_Receive==0x5A)			flag_key=1;
			return 0;//�ް�������
}
/**************************************************************************
�������ܣ�����ɨ��
��ڲ�����˫���ȴ�ʱ��
����  ֵ������״̬ 0���޶��� 1������ 2��˫�� 
**************************************************************************/
u8 Left_RC (int time)
{
			static u8 temp; 
	    static u16 count_double;
			if(Left_Receive>=1)
			{
			  if(++count_double>time)//500ms��
				{
				   if(Left_Receive>=2)  temp=2;//˫��
					 else temp=1;//����
					 Left_Receive=0; //����
				   count_double=0; 	 
				}		
			}
			else temp=0;//�ް�������
			return temp;
}
/**************************************************************************
�������ܣ�����ɨ��
��ڲ�����˫���ȴ�ʱ��
����  ֵ������״̬ 0���޶��� 1������ 2��˫�� 
**************************************************************************/
u8 Right_RC (int time)
{
			static u8 temp; 
	    static u16 count_double;
			if(Right_Receive>=1)
			{
			  if(++count_double>time)//500ms��
				{
				   if(Right_Receive>=2)  temp=2;//˫��
					 else temp=1;//����
					 Right_Receive=0; //����
				   count_double=0; 	 
				}		
			}
			else temp=0;//�ް�������
			return temp;
}
