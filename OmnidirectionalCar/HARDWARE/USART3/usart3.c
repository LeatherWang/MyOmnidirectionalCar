
#include "usart3.h"

 u8 mode_data[2];
 u8 six_data_stop[2]={0X59,0X59};  //停止数据样本
 u8 six_data_start[2]={0X58,0X58};  //启动数据样本

/**************************************************************************
函数功能：串口3初始化
入口参数：pclk2:PCLK2 时钟频率(Mhz)    bound:波特率
返回  值：无
**************************************************************************/
void uart3_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
  mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<3;   //使能PORTB口时钟  
	RCC->APB1ENR|=1<<18;  //使能串口时钟 
	GPIOB->CRH&=0XFFFF00FF; 
	GPIOB->CRH|=0X00008B00;//IO状态设置
	GPIOB->ODR|=1<<10;	  
	RCC->APB1RSTR|=1<<18;   //复位串口1
	RCC->APB1RSTR&=~(1<<18);//停止复位	   	   
	//波特率设置
 	USART3->BRR=mantissa; // 波特率设置	 
	USART3->CR1|=0X200C;  //1位停止,无校验位.
	//使能接收中断
	USART3->CR1|=1<<8;    //PE中断使能
	USART3->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(0,0,USART3_IRQn,2);//组2，最低优先级 
}

/**************************************************************************
函数功能：串口3接收中断
入口参数：无
返回  值：无
**************************************************************************/
static u8 RxState = 0;
static u8 RxBuffer[256];
int USART3_IRQHandler(void)
{	
	if(USART3->SR&(1<<5))//接收到数据
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
函数功能：串口扫描
**************************************************************************/
u8 click_RC (void)
{
			static u8 flag_key=1;//按键按松开标志
	    u8 temp;
			if(flag_key&&Usart3_Receive!=0x5A)
			{
			flag_key=0;
		  if(Usart3_Receive>=0x01&&Usart3_Receive<=0x08)temp=Usart3_Receive;
		  else	if(Usart3_Receive>=0x41&&Usart3_Receive<=0x48)temp=Usart3_Receive-0x40;	
		//	else 	temp=0;
			return temp;	// 按键按下
			}
			else if(Usart3_Receive==0x5A)			flag_key=1;
			return 0;//无按键按下
}
/**************************************************************************
函数功能：串口扫描
入口参数：双击等待时间
返回  值：按键状态 0：无动作 1：单击 2：双击 
**************************************************************************/
u8 Left_RC (int time)
{
			static u8 temp; 
	    static u16 count_double;
			if(Left_Receive>=1)
			{
			  if(++count_double>time)//500ms内
				{
				   if(Left_Receive>=2)  temp=2;//双击
					 else temp=1;//单击
					 Left_Receive=0; //清零
				   count_double=0; 	 
				}		
			}
			else temp=0;//无按键按下
			return temp;
}
/**************************************************************************
函数功能：串口扫描
入口参数：双击等待时间
返回  值：按键状态 0：无动作 1：单击 2：双击 
**************************************************************************/
u8 Right_RC (int time)
{
			static u8 temp; 
	    static u16 count_double;
			if(Right_Receive>=1)
			{
			  if(++count_double>time)//500ms内
				{
				   if(Right_Receive>=2)  temp=2;//双击
					 else temp=1;//单击
					 Right_Receive=0; //清零
				   count_double=0; 	 
				}		
			}
			else temp=0;//无按键按下
			return temp;
}
