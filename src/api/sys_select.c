#include <sys/select.h>
#define T(t) (t*)0;
#define F(t,n) {t *y = &x.n;}
#define C(n) switch(n){case n:;}
static void f()
{
T(time_t)
T(suseconds_t)
T(sigset_t)
T(struct timespec)
T(fd_set)
{
struct timeval x;
F(time_t, tv_sec)
F(suseconds_t, tv_usec)
}
C(FD_SETSIZE)
#ifndef FD_CLR
void(*p_FD_CLR)(int,fd_set*) = FD_CLR;
#endif
#ifndef FD_ISSET
int(*p_FD_ISSET)(int,fd_set*) = FD_ISSET;
#endif
#ifndef FD_SET
void(*p_FD_SET)(int,fd_set*) = FD_SET;
#endif
#ifndef FD_ZERO
void(*p_FD_ZERO)(fd_set*) = FD_ZERO;
#endif
int(*p_pselect)(int,fd_set*restrict,fd_set*restrict,fd_set*restrict,const struct timespec*restrict,const sigset_t*restrict) = pselect;
int(*p_select)(int,fd_set*restrict,fd_set*restrict,fd_set*restrict,struct timeval*restrict) = select;
}