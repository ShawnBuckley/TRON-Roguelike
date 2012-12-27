// TRONLIKE Linux.cc

#include <stdio.h>
#include <math.h>

#include <sys/time.h>
#include <unistd.h>

#include "linux.hh"

void Delay(uint32_t useconds)
{
//	printf("Delay %i\n", useconds);

	usleep(useconds);
}
