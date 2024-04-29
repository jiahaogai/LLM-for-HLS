#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[4][4])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  outer:
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      int k;
      inner_1:
      for (k = 0; k < 4; k++) {
        sol[i][j] += filter[k][j] * orig[i + (-1 + k)][j];
      }
    }
  }
}