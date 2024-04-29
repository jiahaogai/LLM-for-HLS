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
  long p;
  long q;
  long r;
  long s;
  long t;
  long u;
  long v;
  long w;
  long x;
  long y;
  long z;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (k = 1; k < 27 - 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 27 - 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 1; i < 27 - 1; i++) {
        idx = i + ((j + (k * 3)) * 3);
        m = orig[idx - 1] - 2 * orig[idx] + orig[idx + 1];
        n = orig[idx + 3 - 1] - 2 * orig[idx + 3] + orig[idx + 3 + 1];
        o = orig[idx + 9 - 1] - 2 * orig[idx + 9] + orig[idx + 9 + 1];
        p = orig[idx + 15 - 1] - 2 * orig[idx + 15] + orig[idx + 15 + 1];
        q = orig[idx + 21 - 1] - 2 * orig[idx + 21] + orig[idx + 21 + 1];
        r = orig[idx + 27 - 1] - 2 * orig[idx + 27] + orig[idx + 27 + 1];
        sol[idx] = ((-1 * m) - 2 * n - 1 * o + 2 * p + 1 * q + 2 * r) / (8 * 27);
      }
    }
  }
}