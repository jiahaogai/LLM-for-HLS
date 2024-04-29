#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 400 - 1; j++) {
      sol[i][j] = ((filter[0] * orig[i - 1][j - 1]) + (filter[1] * orig[i - 1][j]) + (filter[2] * orig[i - 1][j + 1]) + (filter[3] * orig[i][j - 1]) + (filter[4] * orig[i][j]) + (filter[5] * orig[i][j + 1]) + (filter[6] * orig[i + 1][j - 1]) + (filter[7] * orig[i + 1][j]) + (filter[8] * orig[i + 1][j + 1])) / 41;
    }
  }
//#pragma endscop
}