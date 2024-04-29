#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{21}
 void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  int j_col;
  int flatten_index;
  int pad;
  pad = 1;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj_pad:
  for (j = 0; j < 8; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopi:
    for (i = 0; i < 8; i++) {
      i_col = i - 1 + pad;
      j_col = j - 1 + pad;
      flatten_index = i_col * 8 + j_col;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk:
      for (k = 0; k < 9; k++) {
        k_col = k - 1 + pad;
        sol[flatten_index] += filter[k] * orig[k_col * 8 + j_col];
      }
    }
  }
}