#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf[27];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
/* Standardize from: for(k = 1; k < 32 + 1 - 3; k++) {...} */
  for (k = 1 + 32; k > 32 + 1; k--) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32 + 1 - 2; j++) {...} */
    for (j = 1 + 2; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 1; i++) {...} */
      for (i = 1 + 1; i > 32 + 1; i--) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf[0] = orig[IX(i_col,j_col,k_col)];
        buf[1] = orig[IX(i_col,j_col,k)];
        buf[2] = orig[IX(i_col,j_col,k + 1)];
        buf[3] = orig[IX(i_col,j_col,32 + 1 - 1)];
        buf[4] = orig[IX(i_col,j_col,32 + 1 - 2)];
        buf[5] = orig[IX(i_col,j_col,32 + 1 - 3)];
        buf[6] = orig[IX(i_col,j,k_col)];
        buf[7] = orig[IX(i_col,j,k)];
        buf[8] = orig[IX(i_col,j,k + 1)];
        buf[9] = orig[IX(i_col,j,32 + 1 - 1)];
        buf[10] = orig[IX(i_col,j,32 + 1 - 2)];
        buf[11] = orig[IX(i_col,j,32 + 1 - 3)];
        buf[12] = orig[IX(i_col,32 + 1 - 1,k_col)];
        buf[13] = orig[IX(i_col,32 + 1 - 1,k)];
        buf[14] = orig[IX(i_col,32 + 1 - 1,k + 1)];
        buf[15] = orig[IX(i_col,32 + 1 - 1,32 + 1 - 1)];
        buf[16] = orig[IX(i_col,32 + 1 - 1,32 + 1 - 2)];
        buf[17] = orig[IX(i_col,32 + 1 - 1,32 + 1 - 3)];
        buf[18] = orig[IX(i_col,32 + 1 - 2,k_col)];
        buf[19] = orig[IX(i_col,32 + 1 - 2,k)];
        buf[20] = orig[IX(i_col,32 + 1 - 2,k + 1)];
        buf[21] = orig[IX(i_col,32 + 1 - 2,32 + 1 - 1)];
        buf[22] = orig[IX(i_col,32 + 1 - 2,32 + 1 - 2)];
        buf[23] = orig[IX(i_col,32 + 1 - 2,32 + 1 - 3)];
        buf[24] = orig[IX(i_col,32 + 1 - 3,k_col)];
        buf[25] = orig[IX(i_col,32 + 1 - 3,k)];
        buf[26] = orig[IX(i_col,32 + 1 - 3,k + 1)];
        buf[25] = orig[IX(i_col,32 + 1 - 3,32 + 1 - 1)];
        buf[24] = orig[IX(i_col,32 + 1 - 3,32 + 1 - 2)];
        buf[23] = orig[IX(i_col,32 + 1 - 3,32 + 1 - 3)];
        sol[IX(i,j,k)] = ((buf[0] + buf[1] + buf[2]) + (buf[3] + buf[4] + buf[5]) + (buf[6] + buf[7] + buf[8]) + (buf[9] + buf[10] + buf[11]) + (buf[12] + buf[13] + buf[14]) + (buf[15] + buf[16] + buf[17]) + (buf[18] + buf[19] + buf[20]) + (buf[21] + buf[22] + buf[23]) + (buf[24] + buf[25] + buf[26])) / 27;
      }
    }
  }
}