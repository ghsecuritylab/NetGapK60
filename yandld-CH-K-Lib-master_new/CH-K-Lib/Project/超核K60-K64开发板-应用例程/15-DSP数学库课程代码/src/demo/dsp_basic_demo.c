#include "chlib_k.h"
#include "arm_math.h"
#include "dsp_basic_demo.h"

 /**
 * @brief  ��ʾarm_abs_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-22
 */
void arm_abs_f32_demo(void) {
	/**	
	*	���ȴ���һ������������A(0.0,6.0)
	*	������Կ�����һ��һ�����е�����ʽ��������ʾһ����ά����
	*	��ȻҲ����д��src_vector[1][2] = {{0.0},{-6.0}}; ������ע����ʹ�ù�����ע������ָ���ά����
	*/
	float32_t src_vector[2] = {1.0f,-6.0f};	
	/**�ٴ���һ������������������������Ľ��,ϰ���Խ��ֲ�����������ʼ��Ϊ0*/
	float32_t dst_vector[2] = {0.0f,0.0f};
	/**���ڴ�ӡ��ʼ�����*/
	printf("arm_abs_f32_demo\n\r");
	printf("src_vector[0] = %f src_vector[1] = %f\n\r",src_vector[0],src_vector[1]);
	printf("dst_vector[0] = %f dst_vector[1] = %f\n\r",dst_vector[0],dst_vector[1]);
	/**������ѧ��*/
	printf("start arm_abs...\n\r");
	/**sizeof(src_vector)/sizeof(float32_t) ��ʾ�����������ռ���ֽ���Ȼ�����ÿ��Ԫ��ռ���ֽ��� ���������Ԫ�س���*/
	arm_abs_f32(src_vector,dst_vector,sizeof(src_vector)/sizeof(float32_t));
	printf("arm_abs completed\n\r");
	/**��ӡ���������бȽ�*/
	printf("dst_vector[0] = %f dst_vector[1] = %f\n\r",dst_vector[0],dst_vector[1]);
}

 /**
 * @brief  ��ʾarm_add_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-22
 */
void arm_add_f32_demo(void) {
	/**	
	*	���ȴ�����������������A(0.0,6.0) B(0.0,-13.5)
	*/
	float32_t A[2] = {0.0f,-6.0f};
	float32_t B[2] = {0.0f,-13.5f};	
	/**�ٴ���һ������������������������Ľ��,ϰ���Խ��ֲ�����������ʼ��Ϊ0*/
	float32_t result_vector[2] = {0.0f,0.0f};
	/**���ڴ�ӡ����A,B�ĳ�ʼ�����*/
	printf("arm_add_f32_demo\n\r");
	printf("A = (%f,%f)  B = (%f,%f)\n\r",A[0],A[1],B[0],B[1]);
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
	/**������ѧ��*/
	printf("start arm_add...\n\r");
	/**
		������Ҫע����� ����������ӣ�������ͬά�ȼ���ģ������Ҫ������ͬά�ȵ�������ӣ��뽫��ά��������δ����ά�Ȳ�0
		���� A(0,1,2) + B(3,3),����Ҫ�Լ��Ƚ�B��������ΪB(3,3,0),�������������⣬��ע��
	*/
	arm_add_f32(A,B,result_vector,sizeof(A)/sizeof(float32_t));
	printf("arm_add completed\n\r");
	/**��ӡ���������бȽ�*/
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
}

 /**
 * @brief  ��ʾdot_prod_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-22
 */
void arm_dot_prod_f32_demo(void) {
	/**	
	*	���ȴ�����������������A(1.0,-6.0,10.2) B(2.0,-13.5,-2.5)
	*/
	float32_t A[3] = {1.0f,-6.0f,10.2f};
	float32_t B[3] = {2.0f,-13.5f,-2.5f};	
	/**�ٴ���һ��������������������Ľ��,��Ϊ�����������������һ��������������ϰ���Խ��ֲ�����������ʼ��Ϊ0*/
	float32_t result = 0.0f;
	/**���ڴ�ӡ����A,B�ĳ�ʼ�����*/
	printf("arm_dot_prod_f32_demo\n\r");
	printf("A = (%f,%f,%f)  B = (%f,%f,%f)\n\r",A[0],A[1],A[2],B[0],B[1],B[2]);
	printf("result = %f\n\r",result);
	/**������ѧ��*/
	printf("start arm_dot_prod...\n\r");
	arm_dot_prod_f32(A,B,sizeof(A)/sizeof(float32_t),&result);
	printf("arm_dot_prod completed\n\r");
	/**��ӡ���������бȽ�*/
	printf("result = %f\n\r",result);
}

 /**
 * @brief  ��ʾarm_mult_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-22
 */
void arm_mult_f32_demo(void) {
	/**	
	*	���ȴ�����������������A(3.0,6.0) B(2.0,-13.5)
	*/
	float32_t A[2] = {3.0f,6.0f};
	float32_t B[2] = {2.0f,-13.5f};	
	/**�ٴ���һ��������������������Ľ��,��Ϊ�����������������һ��������������ϰ���Խ��ֲ�����������ʼ��Ϊ0*/
	float32_t result_vector[2] = {0,0};
	/**���ڴ�ӡ����A,B�ĳ�ʼ�����*/
	printf("arm_mult_f32_demo\n\r");
	printf("A = (%f,%f)  B = (%f,%f)\n\r",A[0],A[1],B[0],B[1]);
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
	/**������ѧ��*/
	printf("start arm_mult...\n\r");
	arm_mult_f32(A,B,result_vector,sizeof(A)/sizeof(float32_t));
	printf("arm_mult completed\n\r");
	/**��ӡ���������бȽ�*/
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
}

 /**
 * @brief  ��ʾarm_negate_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-22
 */
void arm_negate_f32_demo(void) {
	/**	
	*	���ȴ���һ������������A(-4.0,-3.0) 
	*/
	float32_t A[2] = {-4.0f,-3.0f};
	/**�ٴ���һ��������������������Ľ��,��Ϊ�����������������һ��������������ϰ���Խ��ֲ�����������ʼ��Ϊ0*/
	float32_t result_vector[2] = {0,0};
	/**���ڴ�ӡ����A�ĳ�ʼ�����*/
	printf("arm_negate_f32_demo\n\r");
	printf("A = (%f,%f)\n\r",A[0],A[1]);
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
	/**������ѧ��*/
	printf("start arm_negate_f32...\n\r");
	arm_negate_f32(A,result_vector,sizeof(A)/sizeof(float32_t));
	printf("arm_negate completed\n\r");
	/**��ӡ���������бȽ�*/
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
}

 /**
 * @brief  ��ʾarm_offset_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-22
 */
void arm_offset_f32_demo(void) {
	/**	
	*	���ȴ���һ������������A(-4.0,-3.0),�ٴ���һ����������ƫ����Offset 
	*/
	float32_t A[2] = {-4.0f,-3.0f};
	float32_t Offset = 18.85;
	/**�ٴ���һ��������������������Ľ��,��Ϊ�����������������һ��������������ϰ���Խ��ֲ�����������ʼ��Ϊ0*/
	float32_t result_vector[2] = {0,0};
	/**���ڴ�ӡ����A�ĳ�ʼ�����*/
	printf("arm_offset_f32_demo\n\r");
	printf("A = (%f,%f) Offset = %f\n\r",A[0],A[1],Offset);
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
	/**������ѧ��*/
	printf("start arm_offset...\n\r");
	arm_offset_f32(A,Offset,result_vector,sizeof(A)/sizeof(float32_t));
	printf("arm_offset completed\n\r");
	/**��ӡ���������бȽ�*/
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
}


 /**
 * @brief  ��ʾarm_scale_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-22
 */
void arm_scale_f32_demo(void) {
	/**	
	*	���ȴ���һ������������A(-4.0,-3.0),�ٴ���һ������������Χ��Scale 
	*/
	float32_t A[2] = {-4.0f,-3.0f};
	float32_t Scale = 1.5f;
	/**�ٴ���һ��������������������Ľ��,��Ϊ�����������������һ��������������ϰ���Խ��ֲ�����������ʼ��Ϊ0*/
	float32_t result_vector[2] = {0,0};
	/**���ڴ�ӡ����A�ĳ�ʼ�����*/
	printf("arm_scale_f32_demo\n\r");
	printf("A = (%f,%f) Scale = %f\n\r",A[0],A[1],Scale);
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
	/**������ѧ��*/
	printf("start arm_scale...\n\r");
	arm_scale_f32(A,Scale,result_vector,sizeof(A)/sizeof(float32_t));
	printf("arm_scale completed\n\r");
	/**��ӡ���������бȽ�*/
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
}

 /**
 * @brief  ��ʾarm_sub_f32����
 * @code
 * @endcode
 * @param  None
 * @retval None
 * @author Rein
 * @update 2014-11-22
 */
void arm_sub_f32_demo(void) {
	/**	
	*	���ȴ�����������������A(0.0,6.0) B(0.0,-13.5)
	*/
	float32_t A[2] = {0.0f,-6.0f};
	float32_t B[2] = {0.0f,-13.5f};	
	/**�ٴ���һ������������������������Ľ��,ϰ���Խ��ֲ�����������ʼ��Ϊ0*/
	float32_t result_vector[2] = {0.0f,0.0f};
	/**���ڴ�ӡ����A,B�ĳ�ʼ�����*/
	printf("arm_sub_f32_demo\n\r");
	printf("A = (%f,%f)  B = (%f,%f)\n\r",A[0],A[1],B[0],B[1]);
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
	/**������ѧ��*/
	printf("start arm_sub...\n\r");
	/**
		������Ҫע����� �������������������ͬά�ȼ���ģ������Ҫ������ͬά�ȵ�����������뽫��ά��������δ����ά�Ȳ�0
		���� A(0,1,2) + B(3,3),����Ҫ�Լ��Ƚ�B��������ΪB(3,3,0),�������������⣬��ע��
	*/
	arm_sub_f32(A,B,result_vector,sizeof(A)/sizeof(float32_t));
	printf("arm_sub completed\n\r");
	/**��ӡ���������бȽ�*/
	printf("result_vector = (%f,%f)\n\r",result_vector[0],result_vector[1]);
}





