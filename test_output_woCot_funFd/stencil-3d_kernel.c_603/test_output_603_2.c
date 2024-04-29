<<<<<<< HEAD
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{30}
=======
#pragma ACCEL kernel
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
<<<<<<< HEAD
  long i_col;
  long j_col;
  long k_row;
  long i_row;
  long j_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_col:
/* Standardize from: for(j_col = 1;j_col < 40;j_col++) {...} */
  for (j_col = 1; j_col < 40; j_col++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col:
/* Standardize from: for(k_col = 1;k_col < 40;k_col++) {...} */
    for (k_col = 1; k_col < 40; k_col++) {
      k_col--;
      i_col = 1L;
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col:
/* Standardize from: for(i_col = 1;i_col < 40;i_col++) {...} */
      for (; i_col < 40; i_col++) {
        i_col--;
        t = ((C0 * (orig[i_col + ((k_col + 1) * 40) + ((j_col + 1) * 40)] + orig[i_col + ((k_col + 1) * 40) + (j_col * 40)] + orig[i_col + (k_col * 40) + (j_col * 40)]) / 3) + (C1 * (orig[i_col + ((k_col + 2) * 40) + ((j_col + 1) * 40)] + orig[i_col + ((k_col + 2) * 40) + (j_col * 40)] + orig[i_col + (k_col * 40) + (j_col * 40)])));
        sol[i_col + ((k_col + 1) * 40) + ((j_col + 1) * 40)] = t;
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj_row:
/* Standardize from: for(j_row = 1;j_row < 40;j_row++) {...} */
  for (j_row = 1; j_row < 40; j_row++) {
=======
  long j_col;
  long i_col;
  long buf[128];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 0; j <= 392 + 0; j++) {
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    loopk_row:
/* Standardize from: for(k_row = 1;k_row < 40;k_row++) {...} */
    for (k_row = 1; k_row < 40; k_row++) {
      k_row--;
      i_row = 1L;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_row:
/* Standardize from: for(i_row = 1;i_row < 40;i_row++) {...} */
      for (; i_row < 40; i_row++) {
        i_row--;
        idx_col = 1L;
        loopk_idx_col:
/* Standardize from: for(k_col = 0;k_col < 40;k_col++) {...} */
        for (k_col = 0; k_col < 40; k_col++) {
          idx_row = 1L;
          loopj_idx_row:
/* Standardize from: for(j_row = 0;j_row < 40;j_row++) {...} */
          for (j_row = 0; j_row < 40; j_row++) {
            idx_row++;
            idx = idx_col + idx_row - 2L;
            t = orig[i_row + (k_row * 40) + (j_row * 40)];
            sol[i_row + (k_row * 40) + (j_row * 40)] = t * 4L + ((orig[i_row + (k_row * 40) + idx] + orig[i_row + idx + (j_row * 40)]) + orig[i_row + (k_col * 40) + j_row]);
          }
        }
        idx_col++;
      }
    }
  }
}
=======
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1 + 0; k <= 392 + 0; k++) {
      k_col = ((392 + 0) * (k - 1)) + 1;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1 + 0; i <= 392 + 0; i++) {
        i_col = ((392 + 0) * (i - 1)) + 1;
        buf[0] = orig[i_col + 0 + ((392 + 0) * 0)] ;
        buf[1] = orig[i_col + 1 + ((392 + 0) * 0)] ;
        buf[2] = orig[i_col + 2 + ((392 + 0) * 0)] ;
        buf[3] = orig[i_col + 3 + ((392 + 0) * 0)] ;
        buf[4] = orig[i_col + 4 + ((392 + 0) * 0)] ;
        buf[5] = orig[i_col + 5 + ((392 + 0) * 0)] ;
        buf[6] = orig[i_col + 6 + ((392 + 0) * 0)] ;
        buf[7] = orig[i_col + 7 + ((392 + 0) * 0)] ;
        buf[8] = orig[i_col + 8 + ((392 + 0) * 0)] ;
        buf[9] = orig[i_col + 9 + ((392 + 0) * 0)] ;
        buf[10] = orig[i_col + 10 + ((392 + 0) * 0)] ;
        buf[11] = orig[i_col + 11 + ((392 + 0) * 0)] ;
        buf[12] = orig[i_col + 12 + ((392 + 0) * 0)] ;
        buf[13] = orig[i_col + 13 + ((392 + 0) * 0)] ;
        buf[14] = orig[i_col + 14 + ((392 + 0) * 0)] ;
        buf[15] = orig[i_col + 15 + ((392 + 0) * 0)] ;
        buf[16] = orig[i_col + 16 + ((392 + 0) * 0)] ;
        buf[17] = orig[i_col + 17 + ((392 + 0) * 0)] ;
        buf[18] = orig[i_col + 18 + ((392 + 0) * 0)] ;
        buf[19] = orig[i_col + 19 + ((392 + 0) * 0)] ;
        buf[20] = orig[
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
