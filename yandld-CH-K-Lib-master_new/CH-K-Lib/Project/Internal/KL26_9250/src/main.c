#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "i2c.h"
#include "pit.h"
#include "dma.h"
#include "mpu9250.h"
#include "protocol.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "inv_mpu.h"
#include "dmp.h"

#include "imu.h"

#include <math.h>

static bool reset_flag = false;
static uint32_t frame_cnt = 0;

void mpu9250_test(void)
{
    mpu9250_init(0);
    struct mpu_config config;
    
    config.afs = AFS_16G;
    config.gfs = GFS_2000DPS;
    config.mfs = MFS_16BITS;
    config.aenable_self_test = false;
    config.genable_self_test = false;
    mpu9250_config(&config);
    
    uint8_t err;
    int16_t ax,ay,az,gx,gy,gz,mx,my,mz;
    
    static int16_t mmx,mmy,mmz;
    while(1)
    {
        err = 0;
    
        err += mpu9250_read_accel_raw(&ax, &ay, &az);
        err += mpu9250_read_gyro_raw(&gx, &gy, &gz);
        err += mpu9250_read_mag_raw(&mx, &my, &mz);
    
        mmx = 0.9*mmx + 0.1*mx;
        mmy = 0.9*mmy + 0.1*my;
        mmz = 0.9*mmz + 0.1*mz;
        
        float angle;
         angle = atan2(mmy, mmx)*57.3;
        if(err)
        {
            printf("!err:%d\r\n", err);
            while(1);
        }

        printf("ax:%05d ay:%05d az:%05d gx:%05d gy:%05d gz:%05d mx:%05d my:%05d mz:%05d %f   \r", ax ,ay, az, gx, gy, gz, mmx, mmy, mmz, angle);  
		GPIO_ToggleBit(HW_GPIOC, 3);
        DelayMs(5);
    }
}

static int transmit_data_init(void)
{
    DMA_InitTypeDef DMAInitStruct;

    DMAInitStruct.chl = HW_DMA_CH0;
    DMAInitStruct.chlTriggerSource = UART0_TRAN_DMAREQ;
    DMAInitStruct.triggerSourceMode = kDMA_TriggerSource_Normal;

    DMAInitStruct.sAddr = 0;
    DMAInitStruct.sAddrIsInc = true;
    DMAInitStruct.sDataWidth = kDMA_DataWidthBit_8;
    DMAInitStruct.sMod = kDMA_ModuloDisable;

    DMAInitStruct.dAddr = (uint32_t)&UART0->D;
    DMAInitStruct.dAddrIsInc = false;
    DMAInitStruct.dDataWidth = kDMA_DataWidthBit_8;
    DMAInitStruct.dMod = kDMA_ModuloDisable;
    DMA_Init(&DMAInitStruct);
    
    DMA_EnableAutoDisableRequest(HW_DMA_CH0, true);
    UART_ITDMAConfig(HW_UART0, kUART_DMA_Tx, true);
    return 0;
}

static int _transmit_data(uint8_t *buf, uint32_t len)
{
    DMA_CancelTransfer(HW_DMA_CH0);
    DMA_SetSourceAddress(HW_DMA_CH0, (uint32_t)buf);
    DMA_SetTransferByteCnt(HW_DMA_CH0, len);
    DMA_EnableRequest(HW_DMA_CH0);
    return 0;
}


extern void PIT_ISR(void);
extern void UART_RX_ISR(uint16_t data);

int mpu9250_read_mag_raw2(int16_t* x, int16_t* y, int16_t* z)
{
    static int16_t mmx,mmy,mmz;
    int r;
    int16_t rmx, rmy,rmz;
    r = mpu9250_read_mag_raw(&rmx, &rmy, &rmz);
    
    mmx = 0.9*mmx + 0.1*rmx;
    mmy = 0.9*mmy + 0.1*rmy;
    mmz = 0.9*mmz + 0.1*rmz;
    
    *x = mmx;
    *y = mmy;
    *z = mmz;
    return r;
}

static imu_io_install_t IMU_IOInstallStruct1 = 
{
    .imu_get_accel = mpu9250_read_accel_raw,
    .imu_get_gyro = mpu9250_read_gyro_raw,
    .imu_get_mag = mpu9250_read_mag_raw2,
};


int main(void)
{
	uint32_t clock;
    uint32_t ret;
	DelayInit();   
    DelayMs(1);
    
    GPIO_QuickInit(HW_GPIOC, 3, kGPIO_Mode_OPP);    
    UART_QuickInit(UART0_RX_PA01_TX_PA02, 115200);    
    printf("HelloWorld\r\n");
    CLOCK_GetClockFrequency(kCoreClock, &clock);
    printf("CoreClock:%dHz\r\n", clock);
    CLOCK_GetClockFrequency(kBusClock, &clock);
    printf("kBusClock:%dHz\r\n", clock);


    PIT_QuickInit(HW_PIT_CH0, 1000*1000);
    PIT_CallbackInstall(HW_PIT_CH0, PIT_ISR);
//   PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, true);

    /* MCU driver init */
    I2C_QuickInit(I2C0_SCL_PB00_SDA_PB01, 100*1000);
    GPIO_QuickInit(HW_GPIOD, 7, kGPIO_Mode_OPP);
	GPIO_WriteBit(HW_GPIOD, 7, 0);
    DelayMs(10);
    
    UART_CallbackRxInstall(HW_UART0, UART_RX_ISR);
 //   UART_ITDMAConfig(HW_UART0, kUART_IT_Rx, true);
    
    mpu9250_init(0);
    struct mpu_config config;
    
    config.afs = AFS_2G;
    config.gfs = GFS_2000DPS;
    config.mfs = MFS_14BITS;
    config.aenable_self_test = false;
    config.genable_self_test = false;
    mpu9250_config(&config);

    //mpu9250_test();
    
    unsigned long sensor_timestamp;
    short gyro[3], accel[3], mag[3], sensors;
    static unsigned char more;
    long quat[4];
 //   float angle[3];
    transmit_user_data send_data;
    uint32_t len;
    static uint8_t buf[64];
//    
//    dmp_init();

    PIT_QuickInit(HW_PIT_CH1, 1000*1000);
    
    printf("dmp init complete\r\n");
    
    transmit_data_init();
    imu_io_install(&IMU_IOInstallStruct1);
    static int time, last_time,load_val;
    int fac_us,fac_ms;
    CLOCK_GetClockFrequency(kBusClock, &fac_us);
    fac_us /= 1000000;
static imu_float_euler_angle_t angle;
static imu_raw_data_t raw_data;


   while(1)
    {
        time = PIT_GetCounterValue(HW_PIT_CH1);
        time = load_val - time;
        
        PIT_ResetCounter(HW_PIT_CH1);
        load_val = PIT_GetCounterValue(HW_PIT_CH1);
        
     //   DisableInterrupts();
        
        ret = imu_get_euler_angle(&angle, &raw_data);
        time /= fac_us;
      //  printf("time:%d \r\n", time);
        halfT = ((float)time)/1000/2000;
      //  EnableInterrupts(); 
        
       // printf("ax:%0f ay:%0f az:%05f   \r", angle.imu_pitch, angle.imu_roll, angle.imu_yaw);  
       
            send_data.trans_gyro[0] = raw_data.gx;
            send_data.trans_gyro[1] = raw_data.gy;
            send_data.trans_gyro[2] = raw_data.gz;
            
            send_data.trans_accel[0] = raw_data.ax;
            send_data.trans_accel[1] = raw_data.ay;
            send_data.trans_accel[2] = raw_data.az;
            
            send_data.trans_mag[0] = raw_data.mx;
            send_data.trans_mag[1] = raw_data.my;
            send_data.trans_mag[2] = raw_data.mz;
            
            
          //  angle[2] = atan2(mag[1], mag[0])*57.3;
            
            send_data.trans_pitch = (int16_t)(angle.imu_pitch*100);
            send_data.trans_roll = (int16_t)(angle.imu_roll*100);
            send_data.trans_yaw = (int16_t)(angle.imu_yaw*10);
            
            /* set buffer */
            len = user_data2buffer(&send_data, buf);
            
            _transmit_data(buf, len);
        
        DelayMs(2);

//        if(reset_flag)
//        {
//            printf("reseting...\r\n");
//            dmp_init();
//            reset_flag = false;
//        }
//        
//        dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);	
//        if (sensors & INV_WXYZ_QUAT )
//        {
//            quat2angle(quat, angle);

//            mpu_get_compass_reg(mag, NULL);
//            
//            send_data.trans_gyro[0] = gyro[0];
//            send_data.trans_gyro[1] = gyro[1];
//            send_data.trans_gyro[2] = gyro[2];
//            
//            send_data.trans_accel[0] = accel[0];
//            send_data.trans_accel[1] = accel[1];
//            send_data.trans_accel[2] = accel[2];
//            
//            send_data.trans_mag[0] = mag[0];
//            send_data.trans_mag[1] = mag[1];
//            send_data.trans_mag[2] = mag[2];
//            
//            
//          //  angle[2] = atan2(mag[1], mag[0])*57.3;
//            
//            send_data.trans_pitch = (int16_t)(angle[0]*100);
//            send_data.trans_roll = (int16_t)(angle[1]*100);
//            send_data.trans_yaw = (int16_t)(angle[2]*10);
//            
//            /* set buffer */
//            len = user_data2buffer(&send_data, buf);
//            
//            _transmit_data(buf, len);

//            GPIO_ToggleBit(HW_GPIOC, 3);
//            frame_cnt++;
//        }
    }
}


void UART_RX_ISR(uint16_t data)
{
    if(data == 'H')
    {
        reset_flag = true;
    }
}


void PIT_ISR(void)
{
   // printf("frame_count:%d\r\n", frame_cnt);
    frame_cnt = 0;
}
