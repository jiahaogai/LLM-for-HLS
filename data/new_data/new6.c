#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define N 64

#define DATA_TYPE float
#define SCALAR_VAL(x) x##f
#define SQRT_FUN(x) sqrtf(x)
#define EXP_FUN(x) expf(x)
#define POW_FUN(x,y) powf(x,y)

void bicg(DATA_TYPE A[N][N], DATA_TYPE p[N], DATA_TYPE r[N], DATA_TYPE s_out[N], DATA_TYPE q_out[N]);

void bicg(DATA_TYPE A[N][N], DATA_TYPE p[N], DATA_TYPE r[N], DATA_TYPE s_out[N], DATA_TYPE q_out[N])
{
    int i, j;

	DATA_TYPE buff_A[N][N];
	DATA_TYPE buff_p[N];
	DATA_TYPE buff_r[N];
	DATA_TYPE buff_s_out[N];
	DATA_TYPE buff_q_out[N];

	lprd_1: for (i = 0; i < N; i++) {
		buff_p[i] = p[i];
		buff_r[i] = r[i];
		buff_s_out[i] = 0;
		buff_q_out[i] = 0;
		lprd_2: for (j = 0; j < N; j++) {
			buff_A[i][j] = A[i][j];
		}
	}

    lp1: for (i = 0; i < N; i++) {
        lp2: for (j = 0; j < N; j++) {
	        buff_s_out[j] = buff_s_out[j] + buff_A[i][j] * buff_r[i];
		}
	}

	lp3: for (i = 0; i < N; i++) {
        lp4: for (j = 0; j < N; j++) {
	        buff_q_out[i] = buff_q_out[i] + buff_A[i][j] * buff_p[j];
	    }
    }

	lpwr: for (i = 0; i < N; i++) {
		s_out[i] = buff_s_out[i];
		q_out[i] = buff_q_out[i];
	}
}
