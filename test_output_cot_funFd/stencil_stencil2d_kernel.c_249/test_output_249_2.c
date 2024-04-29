#pragma ACCEL kernel

void stencil(int orig[25][20],int sol[25][20],int filter[20][20])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 20 - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{20}
      for (k = 0; k < 20; k++) {
        sol[i][j] += filter[k][0] * orig[i][j - 1 + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{20}
      for (k = 0; k < 20; k++) {
        sol[i][j] += filter[k][1] * orig[i][j + k];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{20}
      for (k = 0; k < 20; k++) {
        sol[i][j] += filter[k][2] * orig[i][j + 1 + k];
      }
    }
  }
//#pragma endscop
}