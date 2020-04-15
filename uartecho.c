/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uartecho.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/I2C.h>

/* Example/Board Header files */
#include "Board.h"

/*
 *  ======== mainThread ========
 */
#define SET_SECOND  0x00
#define SET_MIN     0x01
#define SET_HOUR    0x02
#define SET_DOW     0x03 // day of the week
#define SET_DAY     0x04
#define SET_MONTH   0x05
#define SET_YEAR    0x06

<<<<<<< HEAD
<<<<<<< HEAD

=======
=======
>>>>>>> parent of a6e6b16... UART error & SPI still testing
//uint32_t wantedRxchar;            // Number of char *s received so far
//uint8_t rxBuf[32];   // Receive buffer
//uint8_t txBuf[32];   // Transmit buffer
//uint8_t ptr;
//uint8_t endBitFind;

// Callback function
//static void readCallback(UART_Handle handle, void *rxBuf, size_t size)
//{
//    uint8_t i;
    // Copy char *s from RX buffer to TX buffer
//    if(size < 32){
//        for(i = 0; i < size; i++){
//            txBuf[i] = ((uint8_t*)rxBuf)[i];
//        }
        // Echo the char *s received back to transmitter
//        UART_write(handle, txBuf, size);
        // Start another read, with size the same as it was during first call to
        // UART_read()
//        UART_read(handle, rxBuf, wantedRxchar *s);
//    }
//    else {
//        for(i = 0; i < 32; i++) rxBuf[i] = 0;
//    }

    //    if(rxBuf == '\n' && rxBuf == '\r'){
    //        endBitFind++;
    //    }else{
    //        txBuf[ptr] = (uint8_t*)rxBuf;
    //        ptr++;
    //        if(ptr > 63) endBitFind = 2;
    //    }
    //    if(endBitFind == 2){
    //        //txBuf[ptr] = rxBuf;
    //        UART_write(handle, txBuf, ptr);
    //        for(i = 0; i < 64; i++) txBuf[i] = 0;
    //        ptr = 0;
    //        endBitFind = 0;
    //    }

//        UART_read(handle, &txBuf, 1);
//        UART_write(handle, &rxBuf, size);

//}
<<<<<<< HEAD
>>>>>>> parent of a6e6b16... UART error & SPI still testing
=======
>>>>>>> parent of a6e6b16... UART error & SPI still testing
uint8_t bcd2bin(uint8_t val)    { return val - 6 * (val >> 4); }
uint8_t decToBcd(uint8_t val)   { return ( (val/10*16) + (val%10) ); }
uint8_t         I2CtxBuffer[1];
uint8_t         I2CrxBuffer[8];

typedef struct TIMEDATE_{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t DoW;
    uint8_t day;
    uint8_t month;
    uint16_t year;
}timedate_;
typedef struct TIMEDATE_ *TIMEDATE;

void set_DS3231(I2C_Handle handle, uint8_t address, uint16_t data) {
    I2C_Transaction I2C;
    I2CtxBuffer[0] = address;
    I2CtxBuffer[1] = decToBcd(data);
    I2C.slaveAddress = Board_TMP_ADDR;
    I2C.writeBuf = I2CtxBuffer;
    I2C.writeCount = 2;

    I2C.readCount = 0;
    I2C_transfer(handle, &I2C);
    //    if (I2C_transfer(handle, &I2C)) {
    //        return 1;
    //    }else{
    //        return 0;

    //    }

}

char get_DS3231(I2C_Handle handle, TIMEDATE timedate){

    /* Point to the T ambient register and read its 2 char *s */
    I2C_Transaction I2C;
    I2CtxBuffer[0] = 0;
    I2C.slaveAddress = Board_TMP_ADDR;
    I2C.writeBuf = I2CtxBuffer;
    I2C.writeCount = 1;
    I2C.readBuf = I2CrxBuffer;
    I2C.readCount = 7;

    if (I2C_transfer(handle, &I2C)) {
        timedate->second  = bcd2bin(I2CrxBuffer[0] & 0x7F);
        timedate->minute  = bcd2bin(I2CrxBuffer[1]);
        timedate->hour    = bcd2bin(I2CrxBuffer[2]);
        timedate->DoW    = bcd2bin(I2CrxBuffer[3]);
        timedate->day     = bcd2bin(I2CrxBuffer[4]);
        timedate->month   = bcd2bin(I2CrxBuffer[5]);
        timedate->year    = bcd2bin(I2CrxBuffer[6]) + 2000;
        return 1;
    }else return 0;

}
<<<<<<< HEAD
<<<<<<< HEAD
void system_print(UART_Handle handle, uint8_t * data){
    char  TXdata[64], i;
    for(i = 0; i < 64; i++) TXdata[i] = 0;
    sprintf(TXdata,data);
    UART_write(handle, TXdata, sizeof(TXdata));
}
=======

>>>>>>> parent of a6e6b16... UART error & SPI still testing
=======

>>>>>>> parent of a6e6b16... UART error & SPI still testing
void *mainThread(void *arg0)
{
    char  TXdata[64];
    char  RXdata[64];
<<<<<<< HEAD
<<<<<<< HEAD
    UART_Handle uart;
    UART_Params uartParams;
    timedate_ TXtimedate;
    timedate_ RXtimedate;
    I2C_Handle      i2c;
    I2C_Params      i2cParams;
    uint8_t Temp1, Temp2;
=======
=======
>>>>>>> parent of a6e6b16... UART error & SPI still testing

    UART_Handle uart;
    UART_Params uartParams;

    timedate_ TXtimedate;
    timedate_ RXtimedate;


    I2C_Handle      i2c;
    I2C_Params      i2cParams;


    uint8_t Temp1, Temp2;

<<<<<<< HEAD
>>>>>>> parent of a6e6b16... UART error & SPI still testing
=======
>>>>>>> parent of a6e6b16... UART error & SPI still testing
    uint8_t i;
    for(i = 0; i < 64; i++) TXdata[i] = 0;

    GPIO_init();
    UART_init();
    I2C_init();

<<<<<<< HEAD
=======
    /* Turn on user LED */
    GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON);
<<<<<<< HEAD
>>>>>>> parent of a6e6b16... UART error & SPI still testing
=======
>>>>>>> parent of a6e6b16... UART error & SPI still testing

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;
<<<<<<< HEAD
<<<<<<< HEAD

    uart = UART_open(Board_UART0, &uartParams);
    if (uart == NULL) {  while (1);/* UART_open() failed */ }
    system_print(uart,"UART init done:\r\n");
    GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_ON);
=======
//    uartParams.readMode = UART_MODE_CALLBACK; // sets up RX for callback mode
//    uartParams.readCallback = readCallback; // your callback function

    uart = UART_open(Board_UART0, &uartParams);
=======
//    uartParams.readMode = UART_MODE_CALLBACK; // sets up RX for callback mode
//    uartParams.readCallback = readCallback; // your callback function

    uart = UART_open(Board_UART0, &uartParams);
>>>>>>> parent of a6e6b16... UART error & SPI still testing
//    wantedRxchar *s = 1;
//    int rxchar *s = UART_read(uart, rxBuf, wantedRxchar *s);
    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }
    sprintf(TXdata,"UART init done:\r\n");
    UART_write(uart, TXdata, sizeof(TXdata));
<<<<<<< HEAD
>>>>>>> parent of a6e6b16... UART error & SPI still testing
=======
>>>>>>> parent of a6e6b16... UART error & SPI still testing

    /* Create I2C for usage */
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_100kHz;
    i2c = I2C_open(Board_I2C_TMP, &i2cParams);
    if (i2c == NULL) {
        sprintf(TXdata,"I2C Error:\r\n");
        UART_write(uart, TXdata, sizeof(TXdata));
        while (1);
    }
    else {
<<<<<<< HEAD
<<<<<<< HEAD
        system_print(uart,"I2C init done\r\n");
=======
        sprintf(TXdata,"I2C Initialized!\r\n");
        UART_write(uart, TXdata, sizeof(TXdata));
>>>>>>> parent of a6e6b16... UART error & SPI still testing
    }



    /* Start receiving */
    while(1){
        if(UART_read(uart, RXdata, sizeof(RXdata)) > 0){
<<<<<<< HEAD

            if(RXdata[0] == 'T' && RXdata[1] == '1')  GPIO_toggle(Board_GPIO_LED1);
            if(RXdata[0] == 'T' && RXdata[1] == '2')  GPIO_toggle(Board_GPIO_LED2);
            if(RXdata[0] == 'T' && RXdata[1] == '3')  GPIO_toggle(Board_SPI_FLASH_CS);
            
=======
>>>>>>> parent of a6e6b16... UART error & SPI still testing
=======
        sprintf(TXdata,"I2C Initialized!\r\n");
        UART_write(uart, TXdata, sizeof(TXdata));
    }



    /* Start receiving */
    while(1){
        if(UART_read(uart, RXdata, sizeof(RXdata)) > 0){
>>>>>>> parent of a6e6b16... UART error & SPI still testing
            if(RXdata[0] == 'S' && RXdata[1] == 'T'){
                // Read Year first
                Temp1 = RXdata[2] -48;
                Temp2 = RXdata[3] -48;
                TXtimedate.year = Temp1*10 + Temp2;
                // now month
                Temp1 = RXdata[4] -48;
                Temp2 = RXdata[5] -48;
                TXtimedate.month = Temp1*10 + Temp2;
                // now date
                Temp1 = RXdata[6] -48;
                Temp2 = RXdata[7] -48;
                TXtimedate.day = Temp1*10 + Temp2;
                // now Day of Week
                TXtimedate.DoW = RXdata[8] - 48;
                // now Hour
                Temp1 = RXdata[9] -48;
                Temp2 = RXdata[10] -48;
                TXtimedate.hour = Temp1*10 + Temp2;
                // now Minute
                Temp1 = RXdata[11] -48;
                Temp2 = RXdata[12] -48;
                TXtimedate.minute = Temp1*10 + Temp2;
                // now Second
                Temp1 = RXdata[13] -48;
                Temp2 = RXdata[14] -48;
                TXtimedate.second = Temp1*10 + Temp2;

                set_DS3231(i2c, SET_YEAR, TXtimedate.year);
                set_DS3231(i2c, SET_MONTH, TXtimedate.month);
                set_DS3231(i2c, SET_DAY, TXtimedate.day);
                set_DS3231(i2c, SET_DOW, TXtimedate.DoW);
                set_DS3231(i2c, SET_HOUR, TXtimedate.hour);
                set_DS3231(i2c, SET_MIN, TXtimedate.minute);
                set_DS3231(i2c, SET_SECOND, TXtimedate.second);
            }
            if(RXdata[0] == 'T' && RXdata[1] == 'T'){
                sprintf(TXdata,"Got tt youuu...\r\n");
                UART_write(uart, TXdata, sizeof(TXdata));
            }
            if(RXdata[0] == 'R' && RXdata[1] == 'T'){ // RT
                if(get_DS3231(i2c,&RXtimedate)){
                    sprintf(TXdata,"%d:%d:%d   %d/%d/%d d:%d%\r\n",RXtimedate.hour,RXtimedate.minute,RXtimedate.second,RXtimedate.day,RXtimedate.month,RXtimedate.year,RXtimedate.DoW);
                    UART_write(uart, TXdata, sizeof(TXdata));
                }else{
                    sprintf(TXdata,"get_DS3231 Error\r\n");
                    UART_write(uart, TXdata, sizeof(TXdata));
                }
            }

            for(i = 0; i < 64; i++) TXdata[i] = 0;
        }

    }


}




//    /* Loop forever echoing */
//    while (1) {
//        UART_read(uart, &input, 1);
//        UART_write(uart, &input, 1);
//    }
