/* Licensed under the 3-clause BSD License, see the file LICENSE.txt in the root of this directory.*/

#include <stdio.h>
#include <stdint.h>
#include "timestamp.h"

// converts to Julian day number (less the half day offset)
// Caller must ensure valid input
uint32_t jd(int y, int m, int d)
{
	return (1461 * (y+4800+(m-14)/12))/4 +(367 * (m-2-12 * ((m-14)/12)))/12 - (3 * ((y + 4900 + (m - 14)/12)/100))/4 + d-32075;	
}	


// converts a day, month, year and time to a UNIX time-stamp.
// This will overflow in 2038. BSD in 32- and 64-bit machine are now using
// 64-bit integer to avoid the overflow. Linux on 64-bit also returns 64-bit integer
// Caller must ensure valid input
uint32_t unix_time_stamp(int y, int m, int d, int h, int mi, int s)
{
	uint32_t j;
	j = jd(y, m, d)-jd(1970,1,1);
	j = j*24*60*60;
	j += h*60*60 + mi*60 + s;
	return j;
}

// converts day, month, year and time to time stamp used in Active Directory
// It is the number of '100-nano seconds' that has elapsed since 1 Jan 1601.
// It returns a 64-bit unsigned integer
uint64_t adtime(struct dtm z)
{
	uint64_t x;
	
	x=jd(z.y, z.m, z.d) - jd(1601,1,1);
	x=x*24*60*60*10000000L;

	x += ((uint64_t ) z.h *60*60    *10000000UL);
	x += (uint64_t ) z.mi*60*10000000UL;
	x += (uint64_t ) z.s*10000000UL;
	x += (uint64_t ) z.a100s_of_nano_sec/100;
	
	return x;
}

int adtime_inv(uint64_t z, struct dtm *m)
{
	uint64_t a;
	uint32_t e,f,g,h;
	int D,M,Y;
	
	a=z%10000000UL;
	z=z/10000000UL;
	m->a100s_of_nano_sec= a;
	
	a=z%60;
	z=z/60;
	m->s=a;
	
	a=z%60;
	z=z/60;
	m->mi=a;
	
	a=z%24;
	z=z/24;
	m->h=a;
	
	z=z+jd(1601,1,1);

	f = z + 1401 + (((4 * z + 274277) / 146097) * 3) / 4 -38;
	e=4*f+3;
	g=(e%1461)/4;
	h=5*g+2;
	D=(h%153)/5+1;
	M=((h/153+2)%12)+1;
	Y=(e/1461) - 4716 + (12+2-M)/12;

	m->d=D;
	m->m=M;
	m->y=Y;
	return 0;
	
}



