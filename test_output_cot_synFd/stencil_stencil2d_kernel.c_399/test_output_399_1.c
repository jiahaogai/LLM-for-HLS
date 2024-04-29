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
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      inner:
      for (k = -45; k < 46; k++) {
        k_col = k / 8192;
        i_col = i + k_col - 45;
        j_col = j + k - k_col * 8192;
        if ((((i_col >= 0) && (i_col < 8192)) && ((j_col >= 0) && (j_col < 8192))) && ((filter[k + 45] == 1))) {
          t += orig[i_col * 8192 + j_col] * filter[k + 45];
        }
      }
      sol[i * 8192 + j] = t;
    }
  }
}