#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <stdint.h>
#include <inttypes.h>

struct dtm{
	int y;			// year
	unsigned int m;	//month
	unsigned int d; // day
	int unsigned h; // hour
	unsigned int mi; // minute
	unsigned int s;  // seconds
	unsigned int a100s_of_nano_sec; // 100s_of_nano_sec seconds
};
uint32_t jd(int y, int m, int d);
uint32_t unix_time_stamp(int y, int m, int d, int h, int mi, int s);
uint64_t adtime(struct dtm z);
int adtime_inv(uint64_t z, struct dtm *m);


#endif