#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int row;
  int col;
  int flatten_row;
  int flatten_col;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loopj:
  for (j = 0; j < 32; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopk_col:
    for (k_col = 0; k_col < 32; k_col++) {
      int sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        int i_temp = j * 32 + k - 4;
        int k_col_temp = k_col * 32 + k - 4;
        if (((i_temp >= 0) && (i_temp < 8192)) && ((k_col_temp >= 0) && (k_col_temp < 8192))) {
          sum += orig[i_temp] * filter[k];
        }
      }
      sol[j * 32 + k_col] = sum;
    }
  }
}