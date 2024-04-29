#pragma ACCEL kernel

void stencil(int orig[25][25],int sol[25][25],int filter[25])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 25 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 25 - 1; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 25; k++) {
        sol[i][j] += orig[i][k] * filter[k];
      }
    }
  }
//#pragma endscop
}