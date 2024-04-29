#pragma ACCEL kernel

void stencil(double orig[64][128],double sol[64][128],double filter[4][4])
{
  int i;
  int j;
  int k;
  int k_col;
  int k_row;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128 - 1; j++) {
      sol[i][j] = ((double )0);
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k_col = 0; k_col < 4; k_col++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{16}
        for (k_row = 0; k_row < 4; k_row++) {
          k = k_row + 4 * k_col;
          sol[i][j] += filter[k_row][k_col] * orig[i + (-1 + k_row)][j + (-1 + k_col)];;
        }
      }
    }
  }
//#pragma endscop
}