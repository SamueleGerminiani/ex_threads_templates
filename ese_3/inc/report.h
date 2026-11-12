#ifndef _REPORT_HH
#define _REPORT_HH

/* Render report code: you do not need to read or modify this file :)
 *
 * report_row is called by the thread that prints a row, right after
 * printing it, with the row number and the row.
 * report_check reveals code #3 when the rows came out in order, each one
 * once. Call it after joining the threads.
 * The code is bound to the current user and machine.
 */
void report_row(int y, const char *row);
void report_check(void);

#endif
