#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD

#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{1}
=======
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
<<<<<<< HEAD
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopk:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopj:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        t1 = orig[i_col + (j_col + (k_col * 32)) * 39];
        t2 = orig[i_col + ((j_col + (k_col * 32)) + 32) * 39];
        t3 = orig[i_col + ((j_col + (k_col * 32)) + 32L * 32) * 39];
        sol[i + j * 32 + k * 32 * 32] = ((t1 + t2) + t3) / 3L;
=======
  long bound_up;
  long t;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_k:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
     k_col = 40L * 1L * k;
     bound = 1 + 0 + (-1L);
     bound_up = 1 + 0 + (-bound);
     loop_j:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
      j_col = 40L * j;
      t = orig[j_col + bound_up] + orig[j_col + bound] + orig[j_col + (-1L)] + orig[j_col + 1L] + orig[j_col + 40L + bound_up] + orig[j_col + 40L + bound] + orig[j_col + 40L + (-1L)] + orig[j_col + 40L + 1L] ;
      sol[k_col + bound_up] = t;
       loop_i:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = 1L * i;
        t = orig[k_col + i_col + bound_up] + orig[k_col + i_col + bound] + orig[k_col + i_col + (-1L)] + orig[k_col + i_col + 1L] + orig[k_col + i_col + 40L + bound_up] + orig[k_col + i_col + 40L + bound] + orig[k_col + i_col + 40L + (-1L)] + orig[k_col + i_col + 40L + 1L] + (-1L);
        sol[k_col + i_col] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}