#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
<<<<<<< HEAD
  long buf;
=======
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loopk:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
<<<<<<< HEAD
  for (k = 1 + 32L; k < 32 + 1L; k++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j < 32 + 1L; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i < 32 + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        buf = orig[i_col + (j_col + (k_col * 32L)) * 39304L] + 
          orig[i_col + 1L + (j_col + (k_col * 32L)) * 39304L] + 
          orig[i_col + (j_col + 1L + (k_col * 32L)) * 39304L] + 
          orig[i_col + 1L + (j_col + 1L + (k_col * 32L)) * 39304L] + 
          orig[i_col + (j_col + (k_col + 1L) * 32L) * 39304L] + 
          orig[i_col + 1L + (j_col + (k_col + 1L) * 32L) * 39304L] + 
          orig[i_col + (j_col + 1L + (k_col + 1L) * 32L) * 39304L] + 
          orig[i_col + 1L + (j_col + 1L + (k_col + 1L) * 32L) * 39304L];
        sol[i + j * 32L + k * 32L * 32L] = buf;
=======
  for (k = 1 + 32L; k < 32L + 1L; k++) {
     k_col = v_idx(32L, 1L, k);
     k_row = v_idx(32L, k, 1L);
     loopj:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2L; j < 32L + 1L; j++) {
      j_col = v_idx(32L, 1L, j);
      j_row = v_idx(32L, j, 1L);
      loopi:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1L; i < 32L + 1L; i++) {
        i_col = v_idx(32L, 1L, i);
        i_row = v_idx(32L, i, 1L);
        t = orig[k_col] + orig[k_row] + orig[j_col] + orig[j_row] + orig[i_col] + orig[i_row];
        idx = v_idx(32L, i, j);
        sol[idx] = t;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}