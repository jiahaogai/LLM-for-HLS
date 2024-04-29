Code: 
 #pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int flatten_filter[81];
  int i_col;
  int j_col;
  int k;
  int i_row;
  int j_row;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{18}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 400 - 1; j++) {
      i_col = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 9; k++) {
        flatten_filter[i_col++] = filter[k];
      }
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (j_col = 0; j_col < 81; j_col++) {
        i_row = i - 4 + (j_col / 9);
        j_row = j - 4 + (j_col % 9);
        sol[i][j] += flatten_filter[j_col] * orig[i_row][j_row];
      }
    }
  }
}