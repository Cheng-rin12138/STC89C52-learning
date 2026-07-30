#include <REGX52.H>
sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;
/**
   * @brief I2C开始
   * @param 无
   * @retval 无
   */
void I2C_Start()
{
	//1.开始时，二者均为高电平，SCL高电平期间，SDA从高切换到低
	I2C_SDA=1;//结束时SCL均为低电平，低电平变换数据，把SDA拉高确保为1
	I2C_SCL=1;
	
	I2C_SDA=0;
	I2C_SCL=0;
}
/**
   * @brief I2C停止
   * @param 无
   * @retval 无
   */
void I2C_Stop()
{
	//1.结束后，二者均为高电平，SCL高电平期间，SDA从低切换到高
	I2C_SDA=0;//结束前SCL为低电平时变换数据，把SDA拉低确保为0

	I2C_SCL=1;
	I2C_SDA=1;
}
/**
   * @brief I2C发送一个字节
   * @param Byte 要发送的字节
   * @retval 无
   */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		//1.开始时SCL已为低电平，只需先传入最高位到SDA上
		I2C_SDA=Byte&(0x80>>i);
		//2.SCL传输该位，注意手册所需高电平时长，速度过快需延时
		I2C_SCL=1;
		I2C_SCL=0;
	}
}
/**
   * @brief I2C接收一个字节
   * @param 无
   * @retval 接收到的一个字节
   */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	I2C_SDA=1;//主机释放
	
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;//置1读取
		if(I2C_SDA)
			{
				Byte|=(0x80>>i);
			}
		I2C_SCL=0;
	}
	return Byte;
}
/**
   * @brief I2C发送应答
* @param AckBit 应答位，0为应答，1为非应答
   * @retval
   */
void I2C_SendAck(unsigned char AckBit)//可用c51中有特定类型bit
{
	I2C_SDA=AckBit;//SCL低电平读取
	I2C_SCL=1;//拉高读取
	I2C_SCL=0;//拉低
}
/**
   * @brief I2C接收应答
   * @param 无
   * @retval 接收到的应答
   */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA=1;//主机释放，控制权移交从机
	I2C_SCL=1;//拉高读取
	AckBit=I2C_SDA;
	I2C_SCL=0;//拉低
	return AckBit;
}