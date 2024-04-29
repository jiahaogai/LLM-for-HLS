#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
<<<<<<< HEAD
  long idx;
  long kmin;
  long kmax;
  long jmin;
  long jmax;
  long imin;
  long imax;
  long t1;
  long t2;
  long t3;
=======
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
<<<<<<< HEAD
  kmin = 1;
  kmax = 4;
  jmin = 1;
  jmax = 4;
  imin = 1;
  imax = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 0; k < 32; k++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 0; i < 32; i++) {
        idx = i + 32 * j + 32 * 32 * k;
        t1 = orig[idx + 0] + orig[idx + 32];
        t2 = orig[idx + 1] + orig[idx + 31];
        t3 = orig[idx + 32 * 32] + orig[idx + 31 * 32];
        sol[idx] = t1 + t2 + t3;
=======
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
     k_col = k - 1L;
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
      j_col = j - 1L;
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        buf = orig[i + 32L * (j + 32L * k)] ;
        s = 0L;
        loopk_buf:
/* Standardize from: for(k_col = -3; k_col < 0; k_col++) {...} */
        for (k_col = -3L; k_col < 0L; k_col++) {
          loopj_buf:
/* Standardize from: for(j_col = -3; j_col < 0; j_col++) {...} */
          for (j_col = -3L; j_col < 0L; j_col++) {
            loopi_buf:
/* Standardize from: for(i_col = -3; i_col < 0; i_col++) {...} */
            for (i_col = -3L; i_col < 0L; i_col++) {
              s += orig[i_col + 32L * (j_col + 32L * k_col)] ;
            }
          }
        }
        s = buf - s;
        sol[i + 32L * (j + 32L * k)] = s;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}