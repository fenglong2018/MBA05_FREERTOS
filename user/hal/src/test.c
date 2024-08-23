


#include "main.h"
#include "test.h"
#include "stdio.h"

void test_clock(void)	
{
	crm_clocks_freq_type crm_clocks_freq_struct = {0};
	crm_clocks_freq_get(&crm_clocks_freq_struct);
	
	#if LOG
	printf("apb2_freq = \n");
	#endif	

}
















