#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long start;
  long end;
  long step;
  long A;
  long B;
  long C;
  long D;
  long E;
  long F;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_j:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1; j < 392 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1; k < 392 + 1; k++) {
      start = 392 * (k - 1) + (j - 1);
      end = 392 * (k - 1) + j;
      step = 392;
      idx = start;
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loop_i:
      for (i = 1; i < 392 + 1; i++) {
        A = orig[idx - 1 - step];
        B = orig[idx - 1];
        C = orig[idx];
        D = orig[idx + step];
        E = orig[idx + 1];
        F = orig[idx + 1 + step];
        sol[idx] = ((A + B + C + D + E + F) / 6) - C0;
        idx++;
      }
    }
  }
}