#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25][25])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{6}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{62}
      for (k = 0; k < 25; k++) {
        sol[i][j] += filter[k][0] * orig[i][j - 1 + k] + filter[k][1] * orig[i][j + k] + filter[k][2] * orig[i][j + 1 + k];
      }
    }
  }
//#pragma endscop
}