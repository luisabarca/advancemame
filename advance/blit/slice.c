/* Run-length slice test program */

#include <stdio.h>

struct run_slice {
	int whole;
	int up;
	int down;
	int error_t;
	int count;
};

void run_slice_init(struct run_slice* r, int S, int D) {
	if (S > D) {
		/* reduction */
		--S;
		--D;
		r->whole = S / D;
		r->up = (S % D) * 2;
		r->down = D * 2;
		r->error_t = 0;
		r->count = D + 1;
	} else {
		/* expansion */
		r->whole = D / S;
		r->up = (D % S) * 2;
		r->down = S * 2;
		r->error_t = 0;
		r->count = S;
	}
}

#define TEST

void test_red(int S, int D) {
	int total = 0;
	int step = 0;
	struct run_slice r;
	int error_t;
	int count;

	if (S <= D)
		return;

	run_slice_init(&r,S,D);

	error_t = r.error_t;
	count = r.count;

	while (count) {
		unsigned run = r.whole;

		if ((error_t += r.up) > 0) {
			++run;
			error_t -= r.down;
		}
		if (count == 1)
			total += 1;
		else
			total += run;
		++step;
		--count;
	}

	if (total != S || step != D)
		printf("error_t: tot %d, stp %d, src %d, dst %d\n",total,step,S,D);
}

void test_exp(int S, int D) {
	int total = 0;
	int step = 0;
	struct run_slice r;
	int error_t;
	int count;

	if (S >= D)
		return;

	run_slice_init(&r,S,D);

	error_t = r.error_t;
	count = r.count;

	while (count) {
		unsigned run = r.whole;

		if ((error_t += r.up) > 0) {
			++run;
			error_t -= r.down;
		}
		total += run;
		++step;
		--count;
	}

	if (total != D || step != S)
		printf("error_t: tot %d, stp %d, src %d, dst %d\n",total,step,S,D);
}

int main() {
	int i,j;
	for(i=2;i<3000;++i)
		for(j=2;j<3000;++j) {
			if (i > j)
				test_red(i,j);
			if (i < j)
				test_exp(i,j);
		}
	return 0;
}
