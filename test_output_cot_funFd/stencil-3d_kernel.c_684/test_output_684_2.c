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
  long sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_k:
  for (k = 2; k < 32 + 2; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
    for (j = 2; j < 32 + 2; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 2; i < 32 + 2; i++) {
        i_col = i - 2;
        j_col = j - 2;
        k_col = k - 2;
        sum = ((C0 * orig[i_col + 39304 * j_col]) + (C1 * (orig[i_col + 39304 * (j_col + 1)] + orig[i_col + 39304 * (j_col - 1)] + orig[i_col - 1 + 39304 * j_col] + orig[i_col + 39304 * (j_col + 2)] + orig[i_col - 1 + 39304 * (j_col + 2)] + orig[i_col + 39304 * (j_col - 2)] + orig[i_col - 1 + 39304 * (j_col - 2)]))) + orig[i_col + 39304 * j_col];
        buf[0] = sum;
        sum = ((C0 * buf[1]) + (C1 * (buf[2] + buf[0] + orig[i_col - 1 + 39304 * j_col] + buf[5] + orig[i_col - 1 + 39304 * (j_col + 1)] + buf[8] + orig[i_col + 39304 * (j_col - 1)] + buf[7]))) + buf[6];
        sol[i_col + 32768 * j_col] = sum;
        buf[18] = buf[17];
        buf[17] = buf[16];
        buf[16] = buf[15];
        buf[15] = buf[14];
        buf[14] = buf[13];
        buf[13] = buf[12];
        buf[12] = buf[11];
        buf[11] = buf[10];
        buf[10] = buf[9];
        buf[9] = buf[8];
        buf[8] = buf[7];
        buf[7] = buf[6];
        buf[6] = sum;
      }
    }
  }
}