#include "chlib_k.h"
#include "arm_math.h"
#include "dsp_fast_demo.h"
 /**
 * @brief  ��ʾarm_cos_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-27
 */
void arm_cos_f32_demo (void) {
	float pi = 3.14159f; 			//��
	float pi_2 = pi/2; 				//��/2
	float pi_3_2 = pi_2 * 3;		//3��/2
	
	printf("cos(PI) = %f\n\r",arm_cos_f32(pi));	//��ӡCOS(��) �Ľ��Ƽ�����
	printf("cos(PI/2) = %f\n\r",arm_cos_f32(pi_2));//��ӡCOS(��/2)�Ľ��Ƽ�����
	printf("cos(3PI/2) = %f\n\r",arm_cos_f32(pi_3_2));//��ӡCOS(3��/2)�Ľ��Ƽ�����
}

 /**
 * @brief  ��ʾarm_sin_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-27
 */
void arm_sin_f32_demo (void) {
	float pi = 3.14159f; 						//��
	float pi_2 = pi/2; 							//��/2
	float pi_3_2 = pi_2 * 3;					//3��/2
	
	printf("sin(PI) = %f\n\r",arm_sin_f32(pi));	//��ӡSIN(��) �Ľ��Ƽ�����
	printf("sin(PI/2) = %f\n\r",arm_sin_f32(pi_2));//��ӡSIN(��/2)�Ľ��Ƽ�����
	printf("sin(3PI/2) = %f\n\r",arm_sin_f32(pi_3_2));//��ӡSIN(3��/2)�Ľ��Ƽ�����
}

 /**
 * @brief  ��ʾarm_sqrt_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-27
 */
void arm_sqrt_f32_demo(void) {
/**
		���ںܶ�����ƽ���������Ϊ ��������������������Ŀ��Կ�����������һ�ּ����������
	���Գ��濪ƽ���������������źŴ����о���ʹ�� ţ��-����ѷ����Newton-Raphson method��������ƽ����
	˵���˾��ǽ�ƽ�����������ݼ������㣩 ��̩�ռ���չ��������չ�����ǰ��������һ�������鲢�����Ϊ0�����һ��ƽ�����Ľ���ֵ��
	�������������ŵ����f(x) = 0 ������̵����ĸ�������ƽ�������ԡ�����������ʱ�临�Ӷȵ͡�����Ȥ�Ķ��߿�����ѧϰ��
	�������ڲ�ʹ�õľ���Newton-Raphson method�ĵ������������ƽ�����Ľ���ֵ��
*/
	
	float32_t number_4 = 4.0f;
	float32_t number_9 = 9.0f;
	float32_t number_2 = 2.0f;
	float32_t number_3 = 3.0f;
	float32_t result = 0;
	
	arm_sqrt_f32(number_4,&result);				//����4��ƽ�����Ľ���ֵ
	printf("the sqrt of 4 is %f\n\r",result);
	
	arm_sqrt_f32(number_9,&result);				//����9��ƽ�����Ľ���ֵ
	printf("the sqrt of 9 is %f\n\r",result);
	
	arm_sqrt_f32(number_2,&result);				//����2��ƽ�����Ľ���ֵ
	printf("the sqrt of 2 is %f\n\r",result);	

	arm_sqrt_f32(number_3,&result);				//����3��ƽ�����Ľ���ֵ
	printf("the sqrt of 3 is %f\n\r",result);
	
}
