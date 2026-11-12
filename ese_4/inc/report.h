#ifndef _REPORT_HH
#define _REPORT_HH

#include "mandel.h"
#include "queue.h"

/* Render report code: you do not need to read or modify this file :)
 *
 * report_job is called by a worker right after taking a row from the
 * queue, with the row and how many jobs are left in the queue.
 * report_check reveals code #4 when every row was rendered once by the
 * pool. Call it after joining the workers.
 * The code is bound to the current user and machine.
 */
void report_job(int y, int queued);
void report_check(const char frame[HEIGHT][WIDTH + 1], int workers);

#endif
