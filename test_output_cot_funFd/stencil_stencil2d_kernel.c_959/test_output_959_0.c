#
#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[9])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[i][j] += filter[k] * orig[i + (-1 + k)][j + (-1 + k)];
      }
    }
  }
//#pragma endscop
}