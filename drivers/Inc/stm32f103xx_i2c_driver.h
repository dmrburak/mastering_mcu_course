/*
 * stm32f103xx_i2c_driver.h
 *
 *  Created on: 3 Tem 2024
 *      Author: B U R A K
 */

#ifndef INC_STM32F103XX_I2C_DRIVER_H_
#define INC_STM32F103XX_I2C_DRIVER_H_

#include "stm32f103xx.h"

/*
 * Configuration structure for I2Cx peripheral
 */
typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t	 I2C_DeviceAddress; // actually 7 bit, so we used uint8_t
	uint8_t  I2C_AckControl;
	uint8_t  I2C_FMDutyCycle;
}I2C_Config_t;

/*
 * Handle structure for I2Cx peripheral
 */
typedef struct
{
	I2C_RegDef_t 	*pI2Cx;
	I2C_Config_t	 I2CConfig;
	uint8_t		 	*pTxBuffer;		// To store the app. Tx buffer address
	uint8_t			*pRxBuffer;		// To store the app. Rx buffer address
	uint32_t		TxLen;			// To store Tx length
	uint32_t		RxLen;			// To store Rx length
	uint8_t 		TxRxState; 		// To store Communication state
	uint8_t 		DevAddr;		// To store slave/device address
	uint32_t 		RxSize;			// To store Rx size
	uint8_t 		Sr;				// To store repeated start value
}I2C_Handle_t;

/*
 * I2C application states
 */
#define I2C_READY			0
#define I2C_BUSY_IN_RX		1
#define I2C_BUSY_IN_TX		2

/*
 * @I2C_SCLSpeed
 */
#define I2C_SCL_SPEED_SM		100000
#define I2C_SCL_SPEED_FM4K		400000
#define I2C_SCL_SPEED_FM2K		200000

/*
 * @I2C_AckControl
 */
#define I2C_ACK_ENABLE			1
#define I2C_ACK_DISABLE			0

/*
 * @I2C_FMDutyCycle
 */
#define I2C_FM_DUTY_2			0
#define I2C_FM_DUTY_16_9		1


/*
 * I2C related status flag definition
 */
#define I2C_SB_FLAG				(1<<I2C_SR1_SB)
#define I2C_ADDR_FLAG			(1<<I2C_SR1_ADDR)
#define I2C_BTF_FLAG			(1<<I2C_SR1_BTF)
#define I2C_ADD10_FLAG			(1<<I2C_SR1_ADD10)
#define I2C_STOPF_FLAG			(1<<I2C_SR1_STOPF)
#define I2C_RXNE_FLAG			(1<<I2C_SR1_RxNE)
#define I2C_TXE_FLAG			(1<<I2C_SR1_TxE)
#define I2C_BERR_FLAG			(1<<I2C_SR1_BERR)
#define I2C_ARLO_FLAG			(1<<I2C_SR1_ARL)
#define I2C_AF_FLAG				(1<<I2C_SR1_AF)
#define I2C_OVR_FLAG			(1<<I2C_SR1_OVR)
#define I2C_PECERR_FLAG			(1<<I2C_SR1_PECERR)
#define I2C_TIMEOUT_FLAG		(1<<I2C_SR1_TIMEOUT)
#define I2C_SMBALERT_FLAG		(1<<I2C_SR1_SMBALERT)


/*
 * Init and De-init
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/*
 * Peripheral Clock setup
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);	// enable or disable

/*
 * Peripheral control on CR
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);// enables or disables peripheral
void I2C_SSIConfig(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/*
 * Data Send and Receive
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr);

uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

void I2C_SlaveSendData(I2C_RegDef_t *pI2C, uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2C);

/*
 * IRQ Configuration and ISR handling
 */
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void I2C_IRQ_PriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);
/*
 * Other Peripheral Control APIs
 */
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName); // it will return 0 or 1
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);


/*
 * Application callback
 */
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv);


uint32_t RCC_GetPLLOutputClock();
uint32_t RCC_GetPCLK1Value(void);


#endif /* INC_STM32F103XX_I2C_DRIVER_H_ */
