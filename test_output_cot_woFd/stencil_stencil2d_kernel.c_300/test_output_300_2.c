#pragma ACCEL kernel

void stencil(double orig[4][4],double sol[4][4],double filter[4][4])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (int k = 0; k < 4; ++k) {
        sol[i][j] += filter[k][j] * orig[i][k];
      }
    }
  }
}