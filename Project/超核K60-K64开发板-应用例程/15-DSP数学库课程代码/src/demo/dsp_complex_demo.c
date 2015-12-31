#include "dsp_complex_demo.h"

 /**
 * @brief  ��ʾarm_cmplx_conj_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-12-2
 */
 
void arm_cmplx_conj_f32_demo (void) {
	float32_t complex_1 [2*2],		/**����һ����������Ϊ�˱��渴����ʵ�����鲿*/
			  real_1 = 12.5,		/**Ϊ�˱�����⣬�ֱ𴴽�����������ʵ�����鲿*/
			  image_1 = 3.3,
			  real_2 = 5,
			  image_2 = 2.2,
			  complex_2 [2*2];		/**����һ�����鱣���乲�����ʵ�����鲿*/
	complex_1[0] = real_1;			/**����Ҫ����ĸ������鸳ֵ*/
	complex_1[1] = image_1;
	complex_1[2] = real_2;
	complex_1[3] = image_2;
	arm_cmplx_conj_f32(complex_1,complex_2,2);/**�����*/
	/**��ӡ��Ҫ������ĸ�������*/
	printf("real_1 = %f   image_1 = %fj\n\r",real_1,image_1);
	printf("conj_real_1 = %f   conj_image_1 = %fj\n\r",complex_2[0],complex_2[1]);
	/**��ӡ������ɵĸ�������*/
	printf("real_2 = %f   image_2 = %fj\n\r",real_2,image_2);
	printf("conj_real_2 = %f   conj_image_2 = %fj\n\r",complex_2[2],complex_2[3]);
}

 /**
 * @brief  ��ʾarm_cmplx_dot_prod_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-12-6
 */

void arm_cmplx_dot_prod_f32_demo (void) {
	float32_t A[2] = {12.2f,3.5f},
			  B[2] = {4.0f,17.2f},
			  result_real = 0.0f,
			  result_img = 0.0f;
	uint32_t number_of_complex = 1; /**ָ����ÿ���������渴���ĸ���������ֱ���1*/
	
	printf("A = %f + %fj\n\r",A[0],A[1]);
	printf("B = %f + %fj\n\r",B[0],B[1]);
	
	arm_cmplx_dot_prod_f32(A,B,number_of_complex,&result_real,&result_img);

	printf("Result = %f + %fj\n\r",result_real,result_img);

}

 /**
 * @brief  ��ʾarm_cmplx_mag_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-12-6
 */

void arm_cmplx_mag_f32_demo (void) {
	float32_t Complex[6] = {
						10.5f,10.6f,		/**ǰ����ʵ�����������鲿����ͬ*/
						11.2f,56.3f,
						25.5f,7.2f
					 };
	float32_t result[3] = {0,0,0};			/**����������*/
	
	arm_cmplx_mag_f32(Complex,result,3);	/**����*/
	
	printf("Complex_1 = %f + %fj\n\r",Complex[0],Complex[1]);
	printf("Complex_2 = %f + %fj\n\r",Complex[2],Complex[3]);
	printf("Complex_3 = %f + %fj\n\r",Complex[4],Complex[5]);	
	printf("Length of Complex_1 is %f\n\r",result[0]);
	printf("Length of Complex_2 is %f\n\r",result[1]);
	printf("Length of Complex_3 is %f\n\r",result[2]);
}
 
 /**
 * @brief  ��ʾarm_cmplx_mag_squared_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-12-6
 */
void arm_cmplx_mag_squared_f32_demo (void) {
	float32_t Complex[6] = 	{
								10.5f,10.6f,		/**ǰ����ʵ�����������鲿����ͬ*/
								11.2f,56.3f,
								25.5f,7.2f
							};
	float32_t result[3] = {0,0,0};			/**����������*/
	
	arm_cmplx_mag_squared_f32(Complex,result,3);	/**����*/
	
	printf("Complex_1 = %f + %fj\n\r",Complex[0],Complex[1]);
	printf("Complex_2 = %f + %fj\n\r",Complex[2],Complex[3]);
	printf("Complex_3 = %f + %fj\n\r",Complex[4],Complex[5]);	
	printf("Square length of complex_1 is %f\n\r",result[0]);
	printf("Square length of complex_2 is %f\n\r",result[1]);
	printf("Square length of complex_3 is %f\n\r",result[2]);
}
 /**
 * @brief  ��ʾarm_cmplx_mult_cmplx_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-12-6
 */
void arm_cmplx_mult_cmplx_f32_demo (void) {
	float32_t A[4] = 	{
							0.5f,12.3f,
							56.3f,10.0f
						};
	float32_t B[4] = 	{
							1.5f,28.6f,
							52.83f,25.0f
						};
	float32_t result[4] ={0};
	uint32_t number_of_complex = 2;
	
	arm_cmplx_mult_cmplx_f32(A,B,result,number_of_complex);
	/**��ӡ׼������ĸ���*/
	printf("A0 = (%f,%fj)  A1 = (%f,%fj)\n\r",A[0],A[1],A[2],A[3]);
	printf("B0 = (%f,%fj)  B1 = (%f,%fj)\n\r",B[0],B[1],B[2],B[3]);
	/**��ӡ������*/
	printf("result0 = (%f,%fj)  result1 = (%f,%fj)\n\r",result[0],result[1],result[2],result[3]);
}
