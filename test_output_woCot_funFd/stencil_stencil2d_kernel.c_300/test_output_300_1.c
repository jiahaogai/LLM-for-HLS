#pragma ACCEL kernel

void stencil(double orig[4][4],double sol[4][4],double filter[4][4])
{
  int i;
  int j;
  int k;
  int m;
  int n;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 4 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 4 - 1; j++) {
      sol[i][j] = 0.0;
      for (k = 0; k < 4; k++) {
        for (m = 0; m < 4; m++) {
          sol[i][j] += filter[k][m] * orig[i + k][j + m];
        }
      }
    }
  }
//#pragma endscop
}