/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portserial.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

#include "e_port.h"
#include "main.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "mbrtu.h"

 
/* ----------------------- extern functions ---------------------------------*/
extern pxMBFrameCB pxMBFrameCBByteReceived;
extern pxMBFrameCB pxMBFrameCBTransmitterEmpty;
 
/* -----------------------    variables     ---------------------------------*/

#if PORT_USE_UART2
void USART2_IRQHandler(void);
#else
void USART3_IRQHandler(void);
#endif
 
/* ----------------------- Start implementation -----------------------------*/

void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
  /* If xRXEnable enable serial receive interrupts. If xTxENable enable
  * transmitter empty interrupts.
  */
  
  if (xRxEnable) {        
	  SET_BIT((&uartslave)->Instance->CR1, ( USART_CR1_RXNEIE) );
	  	  	  	  	  	  	  	  // PC2 <=> RE ........Receiver Output Enable (Low to enable)
  } else {    
	 CLEAR_BIT((&uartslave)->Instance->CR1, ( USART_CR1_RXNEIE) );
  }
  if (xTxEnable) {    
	  SET_BIT((&uartslave)->Instance->CR1, USART_CR1_TXEIE);
	  	  	  	  	  	  	  	 // PC3 <=> DE……….Driver Output Enable (high to enable)
  } else {
	  CLEAR_BIT((&uartslave)->Instance->CR1, USART_CR1_TXEIE);
  }  
  
}
 
BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
  /* 
  Do nothing, Initialization is handled by MX_USART3_UART_Init() 
  Fixed port, baudrate, databit and parity  
  */

	/*
	 * Please note: when user uses EVEN or ODD parity the Data bit value chose
	 * in CubeMx initialize must be 9 bit
	 */
  return TRUE;
}
 
BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
  /* Put a byte in the UARTs transmit buffer. This function is called
  * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
  * called. */
	uartslave.Instance->TDR = (uint8_t)(ucByte & 0xFFU);
	return TRUE;
  //return (HAL_OK == HAL_UART_Transmit(&uartslave, (uint8_t*)&ucByte, 1, 10));
}
 
BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
  /* Return the byte in the UARTs receive buffer. This function is called
  * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
  */
  *pucByte = (uint8_t)(uartslave.Instance->RDR & (uint8_t)0x00FF);
  return TRUE;
}
 

/**
  * @brief This function handles USART2 global interrupt.
  */

#if PORT_USE_UART2
void USART2_IRQHandler(void){
#else
void USART3_IRQHandler(void){
#endif

  /* USER CODE BEGIN USART2_IRQn 0 */

	uint32_t isrflags   = READ_REG(uartslave.Instance->ISR);
	uint32_t cr1its     = READ_REG(uartslave.Instance->CR1);

    if ( ((isrflags & USART_ISR_RXNE) != 0U)
         && ((cr1its & USART_CR1_RXNEIE) != 0U) )
    {

		  pxMBFrameCBByteReceived();	  //xMBRTUReceiveFSM() in mbrtu.c

//		  __IO uint32_t tmpreg = 0x00U;
//		  tmpreg = (&uartslave)->Instance->ISR;
//		  tmpreg = (&uartslave)->Instance->RDR;
		  SET_BIT((&uartslave)->Instance->RQR,  USART_RQR_RXFRQ);
//		  (void) tmpreg;

		return;
    }

  if((__HAL_UART_GET_FLAG(&uartslave, UART_FLAG_TXE) != RESET) &&(__HAL_UART_GET_IT_SOURCE(&uartslave, UART_IT_TXE) != RESET)) {

	  pxMBFrameCBTransmitterEmpty(); 	  //xMBRTUTransmitFSM() in mbrtu.c

    return ;
  }

  HAL_UART_IRQHandler(&uartslave);

}

