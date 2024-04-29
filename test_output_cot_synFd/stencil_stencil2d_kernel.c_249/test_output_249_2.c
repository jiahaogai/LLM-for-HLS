#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25][25])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 25; j++) {
      sol[i][j] = ((filter[0][0] * orig[i][j]) + (filter[0][1] * orig[i][j + 1]) + (filter[0][2] * orig[i][j + 2]) + (filter[1][0] * orig[i + 1][j]) + (filter[1][1] * orig[i + 1][j + 1]) + (filter[1][2] * orig[i + 1][j + 2]) + (filter[2][0] * orig[i + 2][j]) + (filter[2][1] * orig[i + 2][j + 1]) + (filter[2][2] * orig[i + 2][j + 2])) / 121;
    }
  }
}