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
      sol[i][j] = ((filter[0][0] * orig[i - 1][j - 1]) + (filter[0][1] * orig[i - 1][j]) + (filter[0][2] * orig[i - 1][j + 1]) + (filter[0][3] * orig[i][j - 1]) + (filter[1][0] * orig[i][j]) + (filter[1][1] * orig[i][j + 1]) + (filter[2][0] * orig[i + 1][j - 1]) + (filter[2][1] * orig[i + 1][j]) + (filter[2][2] * orig[i + 1][j + 1]) + (filter[3][0] * orig[i - 1][j + 1]) + (filter[3][1] * orig[i][j + 1]) + (filter[3][2] * orig[i + 1][j + 1])) / 128.0;
    }
  }
//#pragma endscop
}