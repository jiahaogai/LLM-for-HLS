#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long mid;
  long r;
  long tmp;
  long tmp2;
  long tmp3;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_l1:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1L + 32L; i-- > 1L; ) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_l2:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
    for (j = 1L + 32L; j-- > 1L; ) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_l3:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
      for (k = 1L + 32L; k-- > 1L; ) {
        mid = 1L + 32L * 32L;
        r = i * 32L * 32L + j * 32L + k;
        tmp = 0L;
        tmp2 = 0L;
        tmp3 = 0L;
        loop_l4:
        for (idx = r - mid; idx <= r + mid; idx++) {
          if (idx > 0L && idx < 39304L) {
            tmp += orig[idx] * 4L;
            tmp2 += orig[idx] * 2L;
            tmp3 += orig[idx];
          }
        }
        sol[r] = tmp / 16L + tmp2 / 4L + tmp3 / 4L;
      }
    }
  }
}