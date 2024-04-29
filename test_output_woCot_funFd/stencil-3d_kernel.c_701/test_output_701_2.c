#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[27],long sol[27])
{
  long i;
  long j;
  long k;
  long i_col;
  long j_col;
  long k_col;
  long sum;
  long D0;
  long D1;
  long D2;
  D0 = 1;
  D1 = 27;
  D2 = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  loop_x:
  for (i = 0; i < 27; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_y:
    for (j = 0; j < 27; j++) {
      loop_z:
      for (k = 0; k < 27; k++) {
        i_col = (27 + i - 1) % 27;
        j_col = (27 + j - 1) % 27;
        k_col = (27 + k - 1) % 27;
        sum = orig[i_col * 27 + j_col * 1 + k_col] + orig[i_col * 27 + j_col * 1 + (k_col + 1) % 27] + orig[i_col * 27 + (j_col + 1) % 27 * 1 + (k_col + 1) % 27] + orig[(i_col + 1) % 27 * 27 + j_col * 1 + (k_col + 1) % 27] + orig[(i_col + 1) % 27 * 27 + j_col * 1 + k_col] + orig[(i_col + 1) % 27 * 27 + (j_col + 1) % 27 * 1 + k_col] + orig[i_col * 27 + (j_col + 1) % 27 * 1 + k_col];
        sol[i * 27 + j * 1 + k] = (sum + C0) / C1;
      }
    }
  }
}