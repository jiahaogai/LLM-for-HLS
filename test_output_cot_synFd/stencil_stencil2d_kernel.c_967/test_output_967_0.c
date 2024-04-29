#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 1; j < 4; j++) {
      sol[i][j] = ((filter[0][0] * orig[i][j]) + (filter[0][1] * orig[i][j - 1]) + (filter[1][0] * orig[i - 1][j]) + (filter[1][1] * orig[i - 1][j - 1])) / 16;
    }
  }
}