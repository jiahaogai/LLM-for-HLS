#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25][25])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 25; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      int k;
      inner_1:
      for (k = 0; k < 25; k++) {
        sol[i][j] += filter[k][j] * orig[i + (-1 + k)][j];
      }
    }
  }
}