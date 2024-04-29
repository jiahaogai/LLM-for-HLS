#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (int k = 0; k < 3; k++) {
        int idx = i + (-1 + k);
        int idy = j + (-1 + k);
        if (idx >= 0 && idx < 4 && idy >= 0 && idy < 4) {
          sol[i][j] += orig[idx][idy] * filter[k][k];
        }
      }
    }
  }
}