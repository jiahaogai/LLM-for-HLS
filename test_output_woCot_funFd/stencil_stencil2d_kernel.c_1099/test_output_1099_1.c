#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_i;
  int flatten_j;
  int flatten_k;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  loop_i:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_j:
    for (j = 0; j < 256; j++) {
      sol[i * 256 + j] = 0.0;
      loop_k:
      for (k = 0; k < 9; k++) {
        k_col = ((8 * i) + (k / 32)) * 32 + (k % 32);
        i_col = (256 * (k % 32)) + i;
        j_col = (256 * (k / 32)) + j;
        flatten_i = i_col * 256 + j_col;
        flatten_j = k_col * 8 + k % 32;
        flatten_k = k_col * 8 + k / 32;
        sol[i * 256 + j] += filter[k] * orig[flatten_i] << flatten_k;
      }
    }
  }
}