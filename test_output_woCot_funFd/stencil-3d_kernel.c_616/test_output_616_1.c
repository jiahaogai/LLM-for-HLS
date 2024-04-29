#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
<<<<<<< HEAD
  long k_col;
  long j_col;
  long i_col;
  long k_row;
  long j_row;
  long i_row;
  long idx;
  long idx_col;
  long idx_row;
  long t;
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
  loop_k:
/* Standardize from: for(k = 2; k < 39302; k++) {...} */
  for (k = 2; k <= 39301; k++) {
     k_col = k;
     j_col = 0;
     i_col = 0;
     loop_j:
#pragma ACCEL PIPELINE auto{off}
     for (j = 1; j < 393; j++) {
       j_col = j_col + 392;
       i_col = i_col + 1;
       k_row = k - 1;
       j_row = j - 1;
       i_row = 0;
       loop_i:
#pragma ACCEL PIPELINE auto{off}
       for (i = 1; i < 393; i++) {
         i_row = i_row + 1;
         idx_col = k_col * 393 * 393 + j_col * 393 + i_col;
         idx_row = k_row * 393 * 393 + j_row * 393 + i_row;
         idx = idx_col;
         t = C0 * orig[idx_row] + C1 * (orig[idx_row + 1] + orig[idx_row - 1] + orig[idx_col + 393] + orig[idx_col - 393]);
         sol[idx] = t;
       }
       i_row = 0;
     }
     j_row = 0;
   }
   k_row = 0;
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
}