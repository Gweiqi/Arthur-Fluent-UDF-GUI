#include "udf.h"

DEFINE_PROPERTY(saturation_temperature,c,thread)
{
	real temp = C_T(c,thread);
	real sat_temp,sa_temp;
	real w;

	Thread *t_air = THREAD_SUB_THREAD(thread,0); /* ��������������THREAD_SUB_THREAD������ڼ����༶�̣߳����̣߳�ָ�롣 THREAD_SUB_THREAD��������������mixture_thread��phase_domain_index�� �ú������ظ���phase_domain_index�Ľ׶μ��߳�ָ�롣*/
	Thread *t_wv = THREAD_SUB_THREAD(thread,1);
	Thread *t_wl = THREAD_SUB_THREAD(thread,2);

	real p_wv = C_P(c,t_wv); /* ����һ��ˮ�������ѹ������ȡ */

	real operating_p = RP_Get_Real ("operating-pressure");
	real vapor_p = p_wv + operating_p; // absolute pressure = static pressure + operating pressure
	//printf("vapor_p %f",p_wv);

	if(p_wv>0)
	{
		sa_temp = (1723.6425/(8.05573-((double)log10((double)p_wv/133.322)))-233.08)+273.15; // Pressure in Pa to mmHg (Yaws)

		sat_temp=sa_temp;  /* ��sa_temp��ֵ��sat_temp */


	}
	else
		sat_temp=273.15;
	//printf("sat_temp %f",sat_temp);

	return sat_temp;

}