#include "gpio.h"
#include "common.h"
#include "uart.h"

/* CH Kinetis�̼��� V2.50 �汾 */
/* �޸���Ƶ ��ʹ�� CMSIS��׼�ļ� startup_MKxxxx.c �е� CLOCK_SETUP �� */

/*
     ʵ�����ƣ�GPIO�ⲿ�����ж�
     ʵ��ƽ̨����ѻ������
     ����оƬ��MK60DN512ZVQ10
 ʵ��Ч����һ��LED�ƹ������˸��������KEY2��PTE26��ÿ��һ����һ��С�ƽ���˸һ��
          ͨ����������С�Ƶ����𡣶԰��������Ų��������ش����жϵķ�ʽ��
*/

/* �ص������е� array ��32λÿһλ����һ�����ţ�1Ϊ �ý��жϱ����� 0����ý��ж�δ���� */
static void GPIO_ISR(uint32_t array)
{
    printf("enter interrupt, back to RUN now!\r\n");
}

int main(void)
{
    DelayInit();
    
    UART_QuickInit(UART0_RX_PD06_TX_PD07, 115200);
    
    GPIO_QuickInit(HW_GPIOE, 26, kGPIO_Mode_IPU);
    GPIO_CallbackInstall(HW_GPIOE, GPIO_ISR);
    GPIO_ITDMAConfig(HW_GPIOE, 26, kGPIO_IT_FallingEdge, true);
    
    printf("low power STOP mode\r\n");
    
    while(1)
    {
        EnterSTOPMode(false);
        printf("Wake Up!\r\n");
    }
}


