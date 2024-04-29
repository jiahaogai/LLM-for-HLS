#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
  for (j = 1; j < 33 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk_col:
    for (k_col = 1; k_col < 33 - 1; k_col++) {
      i_col = -1 * k_col + 16;
      t = filter[0] * orig[i_col + 0 + (j_col = -1 * j + 16)];
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopk:
      for (k = 1; k < 9; k++) {
        i_col = -1 * k + 16;
        j_col = -1 * k + 16;
        t += filter[k] * (orig[i_col + 0 + j_col] + orig[i_col + 1 + j_col] + orig[i_col + 2 + j_col] + orig[i_col + 3 + j_col] + orig[i_col + 4 + j_col] + orig[i_col + 5 + j_col] + orig[i_col + 6 + j_col] + orig[i_col + 7 + j_col] + orig[i_col + 8 + j_col]);
      }
      sol[i_col + 0 + j_col] = t;
    }
  }
}