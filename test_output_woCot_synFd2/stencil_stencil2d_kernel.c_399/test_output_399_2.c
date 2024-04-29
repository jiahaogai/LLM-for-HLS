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
  int index;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  loop_i:
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 337; j++) {
      flatten_i = i * 337;
      flatten_j = j * 337;
      val = 0;
      loop_k:
      for (k = -4; k <= 4; k++) {
        k_col = k + 4;
        i_col = flatten_i + k_col;
        loop_j_col:
        for (j_col = -4; j_col <= 4; j_col++) {
          index = i_col + j_col;
          val += orig[index] * filter[k_col * 9 + j_col + 4];
        }
      }
      sol[flatten_j + flatten_i] = val;
    }
  }
}