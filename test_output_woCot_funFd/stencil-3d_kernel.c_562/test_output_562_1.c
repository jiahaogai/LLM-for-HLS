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
  long tmp;
  long tmp_row;
  long tmp_cmd;
  long tmp_0;
  long tmp_1;
  long tmp_2;
  long tmp_3;
  long tmp_4;
  long tmp_5;
  long tmp_6;
  long tmp_7;
  long tmp_8;
  long tmp_9;
=======
  long bound;
  long bound_in;
  long r;
  long b;
  long r_col;
  long b_col;
  long tmp;
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_k:
<<<<<<< HEAD
/* Standardize from: for(k = 2; k < 32 + 2; k++) {...} */
  for (k = 2; k <= 34; k++) {
=======
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32L; k < 32L + 1L; k++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
<<<<<<< HEAD
/* Standardize from: for(j = 2; j < 32 + 2; j++) {...} */
    for (j = 2; j <= 34; j++) {
=======
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 32L; j < 32L + 1L; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
<<<<<<< HEAD
/* Standardize from: for(i = 2; i < 32 + 2; i++) {...} */
      for (i = 2; i <= 34; i++) {
        tmp_row = ((k - 2) * 32 + (j - 2)) * 32 + (i - 2);
        tmp_0 = orig[tmp_row];
        tmp_1 = orig[tmp_row + 1];
        tmp_2 = orig[tmp_row + 2];
        tmp_3 = orig[tmp_row + 32];
        tmp_4 = orig[tmp_row + 33];
        tmp_5 = orig[tmp_row + 34];
        tmp_6 = orig[tmp_row + 32 + 1];
        tmp_7 = orig[tmp_row + 32 + 2];
        tmp_8 = orig[tmp_row + 32 + 3];
        tmp_9 = (orig[tmp_row + 1] + orig[tmp_row + 32] + orig[tmp_row + 32 + 1]) + 2L;
        tmp = ((orig[tmp_row + 32 + 3] + tmp_9) + orig[tmp_row + 34]) + 2L;
        buf = tmp_0;
        sol[tmp_row] = tmp;
=======
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 32L; i < 32L + 1L; i++) {
        i_col = i - 1L;
        j_col = j - 1L;
        k_col = k - 1L;
        b = ((k_col * (32L + 1L) + j_col) * (32L + 1L) + i_col) * 2L;
        r = (k_col * (32L + 1L) + j_col) * (32L + 1L) + i_col;
        bound = 32L + 1L - i;
        bound_in = 32L + 1L - j;
        loop_r:
        for (r_col = r; r_col < r + bound; r_col++) {
          b_col = b + bound_in;
          tmp = 0L;
          loop_b:
          for (b_col = b_col; b_col < b_col + bound; b_col++) {
            tmp += orig[b_col] * sol[r_col];
          }
          sol[b_col] = tmp;
        }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}