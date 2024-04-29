#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[27],long sol[27])
{
  long i;
  long j;
  long k;
  long idx;
  long m;
  long n;
  long o;
  long P[8];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (k = 0; k < 27; k++) {
    sol[k] = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 27; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (i = 0; i < 27; i++) {
        idx = i + 27 * (j + 27 * k);
        m = i - 1;
        if (m < 0) {
          m = 0;
        }
        n = j - 1;
        if (n < 0) {
          n = 0;
        }
        o = k - 1;
        if (o < 0) {
          o = 0;
        }
        P[0] = orig[m + 27 * n + 27 * o];
        m = i - 1;
        if (m < 0) {
          m = 0;
        }
        n = j;
        o = k - 1;
        if (o < 0) {
          o = 0;
        }
        P[1] = orig[m + 27 * n + 27 * o];
        m = i - 1;
        if (m < 0) {
          m = 0;
        }
        n = j + 1;
        if (n >= 27) {
          n = 26;
        }
        o = k - 1;
        if (o < 0) {
          o = 0;
        }
        P[2] = orig[m + 27 * n + 27 * o];
        m = i - 1;
        if (m < 0) {
          m = 0;
        }
        n = j + 2;
        if (n >= 27) {
          n = 26;
        }
        o = k;
        P[3] = orig[m + 27 * n + 27 * o];
        m = i;
        if (m >= 27) {
          m = 26;
        }
        n = j - 1;
        if (n < 0) {
          n = 0;
        }
        o = k - 1;
        if (o < 0) {
          o = 0;
        }
        P[4] = orig[m + 27 * n + 27 * o];
        m = i;
        if (m >= 27) {
          m = 26;
        }
        n = j;
        o = k - 1;
        if (o < 0) {
          o = 0;
        }
        P[5] = orig[m + 27 * n + 27 * o];
        m = i;
        if (m >= 27) {
          m = 26;
        }
        n = j + 1;
        if (n >= 27) {
          n = 26;
        }
        o = k - 1;
        if (o < 0) {
          o = 0;
        }
        P[6] = orig[m + 27 * n + 27 * o];
        m = i;
        if (m >= 27) {
          m = 26;
        }
        n = j + 2;
        if (n >= 27) {
          n = 26;
        }
        o = k;
        P[7] = orig[m + 27 * n + 27 * o];
        sol[idx] = ((P[0] + P[1] + P[2] + P[3] + P[4] + P[5] + P[6] + P[7]) + C0) / ((2.0 * 27) * (2.0 * 27) * (2.0 * 27) + C1);
      }
    }
  }
}