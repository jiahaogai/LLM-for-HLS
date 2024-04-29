#pragma ACCEL kernel

void stencil(double orig[4][4],double sol[4][4],double filter[2][2])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = ((filter[0][0] * orig[i][j]) + (filter[0][1] * orig[i][(j + 1) % 4]) + (filter[1][0] * orig[i][(j + 2) % 4]) + (filter[1][1] * orig[i][(j + 3) % 4])) / 16.0;
    }
  }
}