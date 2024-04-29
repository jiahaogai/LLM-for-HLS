#pragma ACCEL kernel

void stencil(int orig[40][40],int sol[40][40],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 39; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 1; j < 39; j++) {
      sol[i][j] = ((filter[0] * orig[i][j]) + (filter[1] * (orig[i][j + 1] + orig[i][j - 1])) + (filter[2] * orig[i][j + 2]) + (filter[3] * (orig[i + 1][j + 1] + orig[i - 1][j + 1])) + (filter[4] * (orig[i + 1][j] + orig[i - 1][j])) + (filter[5] * (orig[i + 1][j - 1] + orig[i - 1][j - 1])) + (filter[6] * orig[i + 2][j]) + (filter[7] * (orig[i + 1][j + 2] + orig[i + 1][j - 2]) + (filter[8] * (orig[i - 1][j + 2] + orig[i - 1][j - 2]))));
    }
  }
//#pragma endscop
}