#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "w25qxx.h"
#include "spi.h"
/* CH Kinetis�̼��� V2.50 �汾 */
/* �޸���Ƶ ���޸� CMSIS��׼�ļ� system_MKxxxx.c �е� CLOCK_SETUP �� */
 
/*
     ʵ�����ƣ�GPIOС��ʵ��
     ʵ��ƽ̨����ѻ������
     ����оƬ��MK60DN512ZVQ10
 ʵ��Ч��: ��ȡ��������SPI-Flash����Ϣͨ�����ڷ��ͳ�ȥ
      С����������˸����˸ʱ����500ms     
*/

#include <string.h>

static int w25qxx_test(void)
{
    uint32_t i, block, buf_size,j;
    static uint8_t buf[4*1024];
    struct w25qxx_attr_t w25qxx;
    
    w25qxx_get_attr(&w25qxx);
    buf_size = sizeof(buf);
    block = w25qxx.size/buf_size;
    
    printf("test unit count:%d\r\n", block);
    
    /* erase chip */
    printf("erase all chips...\r\n");
    w25qxx_erase_chip();
    printf("erase complete\r\n");
    
    for(i=0; i<block; i++)
    {
        printf("verify addr:0x%X(%d)...\r\n", i*buf_size, i);
        for(j=0;j<sizeof(buf);j++)
        {
            buf[j] = j % 0xFF;
        }
        w25qxx_write(i*block, buf, buf_size);
        memset(buf, buf_size, 0);
        w25qxx_read(i*block, buf, buf_size);
        
        /* varify */
        for(j=0;j<sizeof(buf);j++)
        {
            if(buf[j] != (j%0xFF))
            {
                printf("%d error\r\n", j);
            }
        }
    }
    return 0;
}

int main(void)
{
    DelayInit();
    GPIO_QuickInit(HW_GPIOE, 6, kGPIO_Mode_OPP);
    UART_QuickInit(UART0_RX_PD06_TX_PD07, 115200);
    
    printf("w25qxx test\r\n");
    
    /* ��ʼ��SPI2�ӿ� */
    SPI_QuickInit(SPI2_SCK_PD12_SOUT_PD13_SIN_PD14, kSPI_CPOL0_CPHA0, 30*1000*1000);
    
    /* ��ʼ��w25qxx ʹ��CS1Ƭѡ */
    PORT_PinMuxConfig(HW_GPIOD, 15, kPinAlt2); /* SPI2_PCS1 */
    
    /* ��ȡSPI-Flash����Ϣ */
    
    if(w25qxx_init(HW_SPI2, HW_SPI_CS1))
    {
        printf("w25qxx device no found!\r\n");
    }
    else
    {
        struct w25qxx_attr_t w25qxx;
        w25qxx_get_attr(&w25qxx);
        printf("%s(0x%X) detected!\r\n", w25qxx.name, w25qxx.id);
        printf("total size:%dKB\r\n", w25qxx.size/1024);
        printf("block size:%dKB\r\n", w25qxx.block_size/1024);
        printf("sector size:%d\r\n", w25qxx.sector_size);
        printf("page size:%d\r\n", w25qxx.page_size);
    }

    w25qxx_test();
    
    printf("w252qxx test complete\r\n");
    
    while(1)
    {
        GPIO_ToggleBit(HW_GPIOE, 6);
        DelayMs(500);  //С����˸
    }
}

