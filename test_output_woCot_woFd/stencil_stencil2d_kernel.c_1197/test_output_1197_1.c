#pragma ACCEL kernel

void stencil(int orig[DIM][DIM],int sol[DIM][DIM],int filter[FILTER_DIM][FILTER_DIM])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < DIM - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < DIM - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k_col = 0; k_col < FILTER_DIM; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (k_row = 0; k_row < FILTER_DIM; k_row++) {
          k = k_row * FILTER_DIM + k_col;
          sol[i][j] += filter[k_row][k_col] * orig[i + k_row - 1][j + k_col - 1];
        }
      }
    }
  }
//#pragma endscop
}