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
/* Standardize from: for(j = 1; j < 32 + 1 - 3; j++) {...} */
    for (j = 1 + 32; j > 32 + 1; j--) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
/* Standardize from: for(i = 1; i < 32 + 1 - 3; i++) {...} */
      for (i = 1 + 32; i > 32 + 1; i--) {
        buf[0] = orig[index(i - 1,j - 1,k - 1)];
        buf[1] = orig[index(i - 1,j - 1,k)];
        buf[2] = orig[index(i - 1,j - 1,k + 1)];
        buf[3] = orig[index(i - 1,j,k - 1)];
        buf[4] = orig[index(i - 1,j,k)];
        buf[5] = orig[index(i - 1,j,k + 1)];
        buf[6] = orig[index(i - 1,j + 1,k - 1)];
        buf[7] = orig[index(i - 1,j + 1,k)];
        buf[8] = orig[index(i - 1,j + 1,k + 1)];
        buf[9] = orig[index(i,j - 1,k - 1)];
        buf[10] = orig[index(i,j - 1,k)];
        buf[11] = orig[index(i,j - 1,k + 1)];
        buf[12] = orig[index(i,j,k - 1)];
        buf[13] = orig[index(i,j,k)];
        buf[14] = orig[index(i,j,k + 1)];
        buf[15] = orig[index(i,j + 1,k - 1)];
        buf[16] = orig[index(i,j + 1,k)];
        buf[17] = orig[index(i,j + 1,k + 1)];
        buf[18] = orig[index(i + 1,j - 1,k - 1)];
        buf[19] = orig[index(i + 1,j - 1,k)];
        buf[20] = orig[index(i + 1,j - 1,k + 1)];
        buf[21] = orig[index(i + 1,j,k - 1)];
        buf[22] = orig[index(i + 1,j,k)];
        buf[23] = orig[index(i + 1,j,k + 1)];
        buf[24] = orig[index(i + 1,j + 1,k - 1)];
        buf[25] = orig[index(i + 1,j + 1,k)];
        buf[26] = orig[index(i + 1,j + 1,k + 1)];
        sol[index(i,j,k)] = ((buf[0] + buf[1] + buf[2]) + (buf[3] + buf[4] + buf[5]) + (buf[6] + buf[7] + buf[8]) + (buf[9] + buf[10] + buf[11]) + (buf[12] + buf[13] + buf[14]) + (buf[15] + buf[16] + buf[17]) + (buf[18] + buf[19] + buf[20]) + (buf[21] + buf[22] + buf[23]) + (buf[24] + buf[25] + buf[26])) / 82;
      }
    }
    k_col = 32 + 1 - 3;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j_col:
    for (j_col = 0; j_col < 32 + 1; j_col++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{2}
      loop_i_col:
      for (i_col = 0; i_col < 32 + 1; i_col++) {
        orig[index(i_col,j_col,k_col)] = sol[index(i_col,j_col,k_col)];
      }
    }
  }
}