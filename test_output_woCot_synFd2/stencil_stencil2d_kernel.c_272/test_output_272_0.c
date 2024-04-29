#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[4][4])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{126}
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = ((filter[0][0] * orig[i - 1][j - 1]) + (filter[0][1] * orig[i - 1][j]) + (filter[0][2] * orig[i - 1][j + 1]) + (filter[0][3] * orig[i - 1][j + 2]) + (filter[1][0] * orig[i][j - 1]) + (filter[1][1] * orig[i][j]) + (filter[1][2] * orig[i][j + 1]) + (filter[1][3] * orig[i][j + 2]) + (filter[2][0] * orig[i + 1][j - 1]) + (filter[2][1] * orig[i + 1][j]) + (filter[2][2] * orig[i + 1][j + 1]) + (filter[2][3] * orig[i + 1][j + 2]) + (filter[3][0] * orig[i + 2][j - 1]) + (filter[3][1] * orig[i + 2][j]) + (filter[3][2] * orig[i + 2][j + 1]) + (filter[3][3] * orig[i + 2][j + 2])) / 126;
    }
  }
//#pragma endscop
}