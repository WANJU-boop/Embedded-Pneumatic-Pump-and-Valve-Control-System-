#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "LED.h"
#include "string.h"
#include "Timer.h"
#include "Key.h"
#include "Encoder.h"
#include "AD.h"
#include "Motor.h"
uint8_t mode=0;
uint8_t special_mode=0;
uint8_t special_motor=0;
uint8_t change=0;
uint8_t change2=0;
uint8_t flag=0;
uint8_t state=0;
uint8_t time_state=0;
uint8_t pressureValue  = 0;  
uint8_t a  = 0; 
//uint8_t i;	
int16_t Num;
int16_t Num1=0;
uint16_t ADValue;			//定义AD值变量
float Voltage;				//定义电压变量
uint8_t KeyNum;		//定义用于接收按键键码的变量
int main(void)
{
     
    /*模块初始化*/    

	 Serial_Init();		//串口初始化
     OLED_Init();
     Key_Init();
   //  Encoder_Init();
    Motor_Init();
    Motor2_Init();
    Motor3_Init();
    Motor4_Init();
     AD_Init();
    LED_Init();
    Timer_Init();
    
        /*电磁阀初始化*/   
	Motor2_SetSpeed(100);	
    
    Motor3_SetSpeed(0);  
    Motor3_SetSpeed(0); 
        /*电磁阀初始化*/   
  
        OLED_ShowString(1, 1, "mode:");
        OLED_ShowString(1, 6, "neck");
        OLED_ShowString(2, 1, "state:");
        OLED_ShowString(2, 7, "close");
        OLED_ShowString(3, 1, "special:");
        OLED_ShowString(3, 9, "close");    
    
        OLED_ShowString(4, 1, "Num:");
//     printf ("AT+RST\r\n");
//     Delay_ms(1000);
//     printf ("AT+CWMODE=1\r\n");
//     Delay_ms(1000);
//     printf ("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");
//     Delay_ms(1000);
//     printf ("AT+CWJAP=\"iPhone\",\"12345678\"\r\n");
//     Delay_ms(10000);
//     printf ("AT+MQTTUSERCFG=0,1,\"NULL\",\"qszlxTLfKuygODvCypqg&k0tzpCmWMxM\",\"9e93e1b765a9c23e29cb1bfae881f4f09266654610bed76f3c7517b409945dcd\",0,0,\"\"\r\n");
//     Delay_ms(5000);
//     printf ("AT+MQTTCLIENTID=0,\"k0tzpCmWMxM.qszlxTLfKuygODvCypqg|securemode=2\\,signmethod=hmacsha256\\,timestamp=1709293222938|\"\r\n");
//     Delay_ms(5000);
//     printf ("AT+MQTTCONN=0,\"iot-06z00dcwvctccst.mqtt.iothub.aliyuncs.com\",1883,1\r\n");  
//     Delay_ms(10000);     
//     printf ("AT+MQTTSUB=0,\"/k0tzpCmWMxM/qszlxTLfKuygODvCypqg/user/get\",1\r\n"); 
//     Delay_ms(5000);

     
    while (1)
	{ 

        OLED_ShowNum(4, 5,Num1, 5);
        KeyNum = Key_GetNum();		//获取按键键码
		
		if (KeyNum == 1)			//按键1按下
		{
             //更改标志位   
            if(mode==0)
            {
                mode=1;
            }
            else if (mode==1)
            {
                mode=0;
            }
 
                       //充气电磁阀显示
            if(mode==0)
            {
               OLED_ShowString(1, 6, "        "); 
               OLED_ShowString(1, 6, "neck"); 
            }
            else if (mode==1)
            {
                OLED_ShowString(1, 6, "        "); 
                OLED_ShowString(1, 6, "shoulder"); 
            }
		}
     
            if(mode==0)
            {
             Motor2_SetSpeed(100);   
            }
            else if (mode==1)
            {
                Motor2_SetSpeed(0); 
            } 
     
            
            
	if(special_mode ==0)
    {        
		if (KeyNum == 2)			//按键2按下
		{
            change=1;

            
            //更改模式
           if(state==0)
            {
               state=1;
            }
            else if (state==1)
            {
                state=0;
            } 
            
            
		}
    }
             // 特殊模式：正弦波型充放气
         if(KeyNum == 3)            //按键3按下
         {     
             time_state=1;

            //更改标志位                              
             if(special_mode==0)         
             {
                 special_mode=1;                          
             }
             else if(special_mode==1)
             {
                special_mode=0;
             } 
                         //特殊模式显示
            if(special_mode==0)
            {
               OLED_ShowString(3, 9, "        "); 
               OLED_ShowString(3, 9, "close"); 
            }
            else if (special_mode==1)
            {
                OLED_ShowString(3, 9, "        "); 
                OLED_ShowString(3, 9, "open"); 
            }   
         }
           
        //放气电磁阀
             if(special_motor==0)         
             {
                 Motor3_SetSpeed(100);                          
             }
             else if(special_motor==1)
             {
                 Motor3_SetSpeed(-100);  
             } 

         //放气气泵
             if(special_motor==0)         
             {
                 Motor4_SetSpeed(-100);                          
             }
             else if(special_motor==1)
             {
                 Motor4_SetSpeed(100);  
             } 


           
        //充气气泵
           
            if(state==1)
            { 
               Motor_SetSpeed(100);	
            }
            else if(state==0)
            {
              Motor_SetSpeed(-100);
            }




        //串口通信
         if (Serial_RxFlag == 1)		//如果接收到数据包
       {
           change=1;
            if(strstr((const char*)Serial_RxPacket,"on"))
                {
                    state=1; 
                }                  
            if(strstr((const char*)Serial_RxPacket,"off"))
               {
                    state=0;
               }
            Serial_RxFlag = 0;
       }
  
 






                        
       //充气气泵显示
        if(change==1)
        {
            if(state==0)
            {
               OLED_ShowString(2, 7, "        "); 
               OLED_ShowString(2, 7, "close"); 
            }
            else if (state==1)
            {
                OLED_ShowString(2, 7, "        "); 
                OLED_ShowString(2, 7, "open"); 
            } 
         change=0;   
        }
        
 //定时器设置
if(special_mode==1)
        {
             if(time_state==1)
             {      
                Num1=0;
                time_state=0; 
             }            
             if( Num1 <= 15 )
             {
                state=1; 
                 special_motor=0;
                if(flag!=state)
                {
                    flag =state;
                    change=1;
                }                  
             }
             else if(Num1>15 && Num1 <30)
             {

                  state=0; 
                 special_motor=1;
                if(flag!=state)
                {
                    flag =state;
                    change=1;
                }                 
             }
             else if(Num1>45)
             {
                Num1=0;
             }
         
         }
         else if(special_mode ==0)
         {
            if(time_state==1)
            {
                state=0;
                special_motor=0;
                time_state=0;
                change=1;
            }
         }
	if(Num1>1000)
    {
       Num1=0; 
    }        
        
        
      

//            i = i+(Encoder_Get()*10);	        //获取自上此调用此函数后，旋转编码器的增量值，并将增量值加到i上


//  ADValue = AD_GetValue();
//  Voltage = ADValue *(5000.0 / 1023.0);
//  if(Voltage <= 4500) { a = 4500 - Voltage; }//4500即4500mv,本值标准应为4500，但因为一致性的问题，不同的模块会所不同（正负30mV之内），产品实际应用时程序要做相应的清零处理。
//  pressureValue = a * 0.0225;

 



//   sensorValue=ADValue          
//   voltageValue=Voltage
    
   ADValue = AD_GetValue();					//获取AD转换的值
   Voltage = (float)ADValue / 4095 * 99999;		//将AD值线性变换到0~3.3的范围，表示电压
//    if(Voltage>13000)     
//    {
////        state =0;
////        change=1;
//    }

       
       
       
    }
}






void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
        
        Num1 ++;
       		
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}


