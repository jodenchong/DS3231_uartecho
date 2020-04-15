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
#include <ti/drivers/SPI.h>

/* Example/Board Header files */
#include "Board.h"

/*
 *  ======== mainThread ========
 */

#define WREN  6 //write enable
#define WRDI  4 //write disble
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

#define SET_SECOND  0x00
#define SET_MIN     0x01
#define SET_HOUR    0x02
#define SET_DOW     0x03 // day of the week
#define SET_DAY     0x04
#define SET_MONTH   0x05
#define SET_YEAR    0x06

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

void system_print(UART_Handle handle, uint8_t * data){
    char  TXdata[64], i;
    for(i = 0; i < 64; i++) TXdata[i] = 0;
    sprintf(TXdata,data);
    UART_write(handle, TXdata, sizeof(TXdata));
}

void *mainThread(void *arg0)
{
    uint8_t i;
    char  TXdata[64];
    char  RXdata[64];

    uint8_t  SPI_TXdata[32];
    uint8_t  SPI_RXdata[32];

    for(i = 0; i < 32; i++) SPI_TXdata[i] = 0;
    for(i = 0; i < 32; i++) SPI_RXdata[i] = 0;

    UART_Handle uart;
    UART_Params uartParams;

    timedate_ setTimeDate;
    timedate_ getTimeDate;

    I2C_Handle      i2c;
    I2C_Params      i2cParams;

    uint8_t Temp1, Temp2;

    for(i = 0; i < 64; i++) TXdata[i] = 0;
    /* Call driver init functions */
    GPIO_init();
    UART_init();
    I2C_init();
    SPI_init(); 

    /* Turn on user LED */
    GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_ON);
    
    GPIO_write(Board_SPI_FLASH_CS, Board_FLASH_CS_ON);

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 115200;
    //    uartParams.readMode = UART_MODE_CALLBACK; // sets up RX for callback mode
    //    uartParams.readCallback = readCallback;   // your callback function

    uart = UART_open(Board_UART0, &uartParams);
    if (uart == NULL) { while (1); /* UART_open() failed */ }
    system_print(uart,"UART init done:\r\n");
    
    /* Create I2C for usage ---------------------------------------  */
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_100kHz;
    i2c = I2C_open(Board_I2C_TMP, &i2cParams);
    if (i2c == NULL) {
        system_print(uart,"I2C Error:\r\n");
        while (1);
    }
    else {
        system_print(uart,"I2C Initialized!\r\n");
    }

    /* Create SPI for usage ---------------------------------------  */
    SPI_Handle masterSpi;
    SPI_Transaction masterTransaction;
    SPI_Params spiParams;
    UInt transferOK;

    /* Initialize SPI handle as default master */
    SPI_Params_init(&spiParams);
    spiParams.transferMode = SPI_MODE_BLOCKING;
    spiParams.transferTimeout = SPI_WAIT_FOREVER;
    spiParams.transferCallbackFxn = NULL;
    spiParams.mode = SPI_MASTER;
    spiParams.bitRate = 4000000;
    spiParams.dataSize = 8;

    masterSpi = SPI_open(Board_SPI0, &spiParams);
    if (masterSpi == NULL) {
        system_print(uart,"Error initializing SPI\r\n");
    }
    else {
        system_print(uart,"SPI initialized\r\n");


        /* Initialize master SPI transaction structure */
        GPIO_write(Board_SPI_FLASH_CS, Board_FLASH_CS_ON);
        masterTransaction.count = 1;
        SPI_TXdata[0] = WREN;
        SPI_TXdata[1] = NULL;
        // SPI_TXdata[4] = NULL;
        masterTransaction.txBuf = &SPI_TXdata;
        transferOK = SPI_transfer(masterSpi, &masterTransaction);
        GPIO_write(Board_SPI_FLASH_CS, Board_FLASH_CS_OFF);


        /* Initialize master SPI transaction structure */
        GPIO_write(Board_SPI_FLASH_CS, Board_FLASH_CS_ON);
        masterTransaction.count = 4;
        SPI_TXdata[0] = READ;
        SPI_TXdata[1] = 0x00;
        SPI_TXdata[2] = 0x00;
        // SPI_TXdata[3] = 0x00;
        // SPI_TXdata[4] = 0x00;
        SPI_TXdata[3] = NULL;
        // SPI_TXdata[4] = NULL;
        masterTransaction.txBuf = &SPI_TXdata;
        masterTransaction.rxBuf = &SPI_RXdata;
        transferOK = SPI_transfer(masterSpi, &masterTransaction);
        GPIO_write(Board_SPI_FLASH_CS, Board_FLASH_CS_OFF);
        if(transferOK) {
            /* Print contents of master receive buffer */
            sprintf(TXdata,"First Read: %s\n", SPI_RXdata);
            UART_write(uart, TXdata, sizeof(TXdata));
        }
        else {
            system_print(uart,"Unsuccessful master SPI transfer\r\n");
        }


        /* Initialize master SPI transaction structure */
        GPIO_write(Board_SPI_FLASH_CS, Board_FLASH_CS_ON);
        masterTransaction.count = 4;
        SPI_TXdata[0] = WRITE;
        SPI_TXdata[1] = 0x00;
        SPI_TXdata[2] = 0x00;
        // SPI_TXdata[3] = 0x00;
        // SPI_TXdata[4] = 0x00;
        SPI_TXdata[3] = 0x55;
        SPI_TXdata[4] = NULL;
        // SPI_TXdata[4] = NULL;
        masterTransaction.txBuf = &SPI_TXdata;
        // masterTransaction.rxBuf = &SPI_RXdata;
        transferOK = SPI_transfer(masterSpi, &masterTransaction);
        GPIO_write(Board_SPI_FLASH_CS, Board_FLASH_CS_OFF);

        // if(transferOK) {
        //     /* Print contents of master receive buffer */
        //     sprintf(TXdata,"Write: done\n");
        //     UART_write(uart, TXdata, sizeof(TXdata));
        // }
        // else {
        //     system_print(uart,"Unsuccessful master SPI transfer\r\n");
        // }

        /* Initialize master SPI transaction structure */


        GPIO_write(Board_SPI_FLASH_CS, Board_FLASH_CS_ON);
        masterTransaction.count = 4;
        SPI_TXdata[0] = READ;
        SPI_TXdata[1] = 0x00;
        SPI_TXdata[2] = 0x00;
        // SPI_TXdata[3] = 0x00;
        // SPI_TXdata[4] = 0x00;
        SPI_TXdata[3] = NULL;
        // SPI_TXdata[4] = NULL;
        masterTransaction.txBuf = &SPI_TXdata;
        masterTransaction.rxBuf = &SPI_RXdata;

        /* Initiate SPI transfer */
        transferOK = SPI_transfer(masterSpi, &masterTransaction);
        GPIO_write(Board_SPI_FLASH_CS, Board_FLASH_CS_OFF);

        if(transferOK) {
            /* Print contents of master receive buffer */
            sprintf(TXdata,"Second Read: %s\n", SPI_RXdata);
            UART_write(uart, TXdata, sizeof(TXdata));
        }
        else {
            system_print(uart,"Unsuccessful master SPI transfer\r\n");
        }
    }

    /* Start receiving */
    while(1){
        if(UART_read(uart, RXdata, sizeof(RXdata)) > 0){
            if(RXdata[0] == 'T' && RXdata[1] == 'T'){
                system_print(uart,"Got tt youuu...\r\n");
            }

            if(RXdata[0] == 'T' && RXdata[1] == '1')  GPIO_toggle(Board_GPIO_LED1);
            if(RXdata[0] == 'T' && RXdata[1] == '2')  GPIO_toggle(Board_GPIO_LED2);
            if(RXdata[0] == 'T' && RXdata[1] == '3')  GPIO_toggle(Board_SPI_FLASH_CS);


            if(RXdata[0] == 'S' && RXdata[1] == 'T'){
                // Read Year first
                Temp1 = RXdata[2] -48;
                Temp2 = RXdata[3] -48;
                setTimeDate.year = Temp1*10 + Temp2;
                // now month
                Temp1 = RXdata[4] -48;
                Temp2 = RXdata[5] -48;
                setTimeDate.month = Temp1*10 + Temp2;
                // now date
                Temp1 = RXdata[6] -48;
                Temp2 = RXdata[7] -48;
                setTimeDate.day = Temp1*10 + Temp2;
                // now Day of Week
                setTimeDate.DoW = RXdata[8] - 48;
                // now Hour
                Temp1 = RXdata[9] -48;
                Temp2 = RXdata[10] -48;
                setTimeDate.hour = Temp1*10 + Temp2;
                // now Minute
                Temp1 = RXdata[11] -48;
                Temp2 = RXdata[12] -48;
                setTimeDate.minute = Temp1*10 + Temp2;
                // now Second
                Temp1 = RXdata[13] -48;
                Temp2 = RXdata[14] -48;
                setTimeDate.second = Temp1*10 + Temp2;

                set_DS3231(i2c, SET_YEAR, setTimeDate.year);
                set_DS3231(i2c, SET_MONTH, setTimeDate.month);
                set_DS3231(i2c, SET_DAY, setTimeDate.day);
                set_DS3231(i2c, SET_DOW, setTimeDate.DoW);
                set_DS3231(i2c, SET_HOUR, setTimeDate.hour);
                set_DS3231(i2c, SET_MIN, setTimeDate.minute);
                set_DS3231(i2c, SET_SECOND, setTimeDate.second);
            }
            if(RXdata[0] == 'R' && RXdata[1] == 'T'){ // RT
                if(get_DS3231(i2c,&getTimeDate)){
                    sprintf(TXdata,"%d:%d:%d   %d/%d/%d d:%d\r\n",getTimeDate.hour \
                                                                ,getTimeDate.minute \
                                                                ,getTimeDate.second \
                                                                ,getTimeDate.day \
                                                                ,getTimeDate.month \
                                                                ,getTimeDate.year \
                                                                ,getTimeDate.DoW);
                    UART_write(uart, TXdata, sizeof(TXdata));
                }else{
                    system_print(uart,"get_DS3231 Error\r\n");
                }
            }
            GPIO_toggle(Board_GPIO_LED2);
            for(i = 0; i < 64; i++) TXdata[i] = 0;
        }

    }


}




//    /* Loop forever echoing */
//    while (1) {
//        UART_read(uart, &input, 1);
//        UART_write(uart, &input, 1);
//    }
