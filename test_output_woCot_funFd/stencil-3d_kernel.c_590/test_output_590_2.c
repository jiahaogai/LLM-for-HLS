Code: #pragma ACCEL kernel

void kernel_stencil(int C0,int C1,double orig[39304],double sol[32768])
{
  int i;
  int j;
  int k;
  int k_col;
  int j_col;
  int i_col;
  double buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  loop_k:
  for (k = 2; k < 39304 - 2; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_j:
    for (j = 2; j < 39304 - 2; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 2; i < 39304 - 2; i++) {
        i_col = i - 2;
        j_col = j - 2;
        k_col = k - 2;
        buf = orig[i_col + 39304 * (j_col + 39304 * k_col)] + 0.1 * ((((0.5 * orig[i_col + 39304 * (j_col + 39304 * k_col)]) + (0.5 * orig[i_col + 1 + 39304 * (j_col + 39304 * k_col)])) + ((0.5 * orig[i_col - 1 + 39304 * (j_col + 39304 * k_col)]) + (0.5 * orig[i_col + 39304 * (j_col + 1 + 39304 * k_col)]))) + ((((0.5 * orig[i_col + 39304 * (j_col + 39304 * k_col)]) + (0.5 * orig[i_col + 39304 * (j_col - 1 + 39304 * k_col)])) + ((0.5 * orig[i_col + 39304 * (j_col + 39304 * k_col)]) + (0.5 * orig[i_col + 39304 * (j_col + 39304 * (k_col + 1))])))));
        sol[i_col + 39304 * (j_col + 39304 * k_col)] = buf;
      }
    }
  }
}