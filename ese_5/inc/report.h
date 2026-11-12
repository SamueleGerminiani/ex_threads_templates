#ifndef _REPORT_HH
#define _REPORT_HH

#include "mandel.h"

/* Render report code: you do not need to read or modify this file :)
 *
 * report_check reveals code #5 when the frame in the shared segment is
 * right and every child was waited. Call it after the wait loop, before
 * detaching. The code is bound to the current user and machine.
 */
void report_check(int shmid, const char frame[HEIGHT][WIDTH + 1], int children);

#endif
