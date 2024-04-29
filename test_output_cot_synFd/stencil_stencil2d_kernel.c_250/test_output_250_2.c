#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      int k_col = -1 * pad;
      int j_col = -1 * pad;
      int i_col = -1 * pad;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      filter:
      for (k = 0; k < 9; k++) {
        j_col++;
        i_col++;
        int index = i_col * 8 + j_col;
        t += orig[index] * filter[k];
      }
      sol[i * 8 + j] = t;
    }
  }
}