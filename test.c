#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

#include "timestamp.h"

int main()
{
	uint64_t x;
	uint32_t u;
	
	struct dtm g={1786, 8, 31,15,56,17,123456}, M;
	
	x=jd(2000,1,1);
	
	printf("jd = %"PRId64"\n", x);
	u=unix_time_stamp(1970,1,1,1,5,3);
	printf("jd = %u\n", u);
	x=adtime(g);
	printf("x = %"PRId64"\n", x);
	
	adtime_inv(x, &M);
	
	printf("\n\n%u/%u/%u  %i:%i:%i \t%u\n",M.d, M.m, M.y, M.h,M.mi,M.s,M.a100s_of_nano_sec);
	
	u=unix_time_stamp(2009,1,21,4,5,0);
	printf("UTS = %u", u);

	printf("\n\ntest 2:\n");
	x = 133573348900000000ul;
	adtime_inv(x, &M);
	printf("\n\n%u/%u/%u  %i:%i:%i \t%u\n",M.d, M.m, M.y, M.h,M.mi,M.s,M.a100s_of_nano_sec);
	//it should give the time of 2024/4/11 18:48:10 0 GMT as per https://www.epochconverter.com/ldap
	return 0;
}
