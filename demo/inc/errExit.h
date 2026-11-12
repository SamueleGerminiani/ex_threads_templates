#ifndef _ERREXIT_HH
#define _ERREXIT_HH

/* errExit prints the error message of the last failed system call and
 * terminates the process. errExitThread does the same for a pthread
 * function, which returns the error number instead of setting errno. */
void errExit(const char *msg);
void errExitThread(const char *msg, int rc);

#endif
