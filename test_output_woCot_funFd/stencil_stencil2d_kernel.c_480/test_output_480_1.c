Code: #pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int flatten_filter[81];
  int i_col;
  int j_col;
  int k;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 400 - 1; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        i_col = i + ((k / 3) - 1);
        j_col = j + ((k % 3) - 1);
        flatten_filter[k] = orig[i_col][j_col];
      }
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_1:
      for (k = 0; k < 9; k++) {
        sol[i][j] += filter[k] * flatten_filter[k];
      }
    }
  }
}