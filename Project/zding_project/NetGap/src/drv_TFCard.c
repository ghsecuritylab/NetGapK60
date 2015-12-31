#include <rtthread.h>
#include "chlib_k.h"
#include <rtdevice.h>
#include <drv_TFCard.h>

static struct rt_device tf_device;

/*tf��init device����*/
static rt_err_t rt_tf_init(rt_device_t dev)
{
	//if the dev is not acticated, then activate it
    if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED)){
        dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
    }
    return RT_EOK;
}

/*tf��open device����*/
static rt_err_t rt_tf_open(rt_device_t dev, rt_uint16_t oflag)
{
    //��dev��open_flag��λ�Զ�д��ʽ���豸
    dev->open_flag |= RT_DEVICE_OFLAG_RDWR;
    return RT_EOK;
}
/*tf��close device����*/
static rt_err_t rt_tf_close(rt_device_t dev)
{
	return RT_EOK;
}
/*tf��indicate����*/
static rt_err_t rt_tf_indicate(rt_device_t dev, rt_size_t size)
{
    return RT_EOK;
}

rt_err_t tf_device_init(){
    /*�����豸��������*/
    tf_device.type 		= RT_Device_Class_Block;
    tf_device.rx_indicate = rt_tf_indicate;
    tf_device.tx_complete = RT_NULL;
    /*���������豸�����ӿں���*/
    tf_device.init      = rt_tf_init;
    tf_device.open      = rt_tf_open;
    tf_device.close     = rt_tf_close;
    tf_device.read      = RT_NULL;
    tf_device.write     = RT_NULL;
    tf_device.control   = RT_NULL;
    tf_device.user_data = RT_NULL;
    
    /*ע��һ��TF���豸,��tf_deviceע��Ϊsd0�豸����ʽΪ��д�豸*/
    return rt_device_register(&tf_device,"sd0",RT_DEVICE_FLAG_RDWR);      
}

INIT_DEVICE_EXPORT(tf_device_init);

