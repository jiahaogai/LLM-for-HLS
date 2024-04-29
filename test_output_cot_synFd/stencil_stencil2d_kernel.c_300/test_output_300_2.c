#pragma ACCEL kernel

void stencil(double orig[4][4],double sol[4][4],double filter[4][4])
{
  int i;
  int j;
  int k;
  int n;
  int m;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 4; k++) {
        n = i - 1 + k;
        n = n >= 0 ? n : 0;
        n = n < 4 ? n : 3;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        for (m = 0; m < 4; m++) {
          int idx = n * 4 + m;
          int idy = i * 4 + j;
          sol[idy][idx] += filter[k][m] * orig[idy][idx];
        }
      }
    }
  }
//#pragma endscop
}