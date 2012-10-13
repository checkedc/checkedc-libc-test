#include <stdint.h>
#include <stdio.h>
#include "util.h"

static struct l_i t[] = {
#if LDBL_MANT_DIG == 53
#include "sanity/lround.h"

#elif LDBL_MANT_DIG == 64
#include "sanity/lroundl.h"

#endif
};

int main(void)
{
	#pragma STDC FENV_ACCESS ON
	long long yi;
	float d;
	int e, i, err = 0;
	struct l_i *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;

		if (p->r < 0)
			continue;
		fesetround(p->r);
		feclearexcept(FE_ALL_EXCEPT);
		yi = lroundl(p->x);
		e = fetestexcept(INEXACT|INVALID|DIVBYZERO|UNDERFLOW|OVERFLOW);

		if (!checkexcept(e, p->e, p->r)) {
			printf("%s:%d: bad fp exception: %s lroundl(%La)=%lld, want %s",
				p->file, p->line, rstr(p->r), p->x, p->i, estr(p->e));
			printf(" got %s\n", estr(e));
			err++;
		}
		if (yi != p->i) {
			printf("%s:%d: %s lroundl(%La) want %lld got %lld\n",
				p->file, p->line, rstr(p->r), p->x, p->i, yi);
			err++;
		}
	}
	return !!err;
}
