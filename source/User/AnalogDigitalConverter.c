#include "AnalogDigitalConverter.h"

int Analog_Digital_Converter_Init()
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1, ENABLE );
	
	//6分频12M,小于14M
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//ADC恢复默认值
	ADC_DeInit(ADC1);
	
	//独立模式
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	//单通道模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	
	//单次转换模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	
	//转换由软件启动，不是外部启动
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	//ADC数据右对齐
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	//顺序进行ADC转换的数目
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC1, &ADC_InitStructure);
	//使能ADC1
	ADC_Cmd(ADC1, ENABLE);  
  //重置校准    
  ADC_ResetCalibration(ADC1); 
  //重置状态寄存器     
  while(ADC_GetResetCalibrationStatus(ADC1)); 
  //开始校准    
  ADC_StartCalibration(ADC1); 
  //等待校准结束 
  while(ADC_GetCalibrationStatus(ADC1));      
  //软件启动功能   
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);     
	
	return 0;
}

u16 Get_ADC_Data(u8 channel)
{
	u16 value = 0;
	//设置指定通道组合，设置转化顺序和采样时间
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5 );				    
  //开始采样
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);			
	//等待结束
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	
	value = ADC_GetConversionValue(ADC1);
	return value;	
}






























