#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27],double sol[27])
{
  double C[3][3][3];
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  for (i = 0; i < 3; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 3; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 3; k++) {
        C[i][j][k] = orig[i + (3 * j) + (3 * 3 * k)];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 3; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 3; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 3; k++) {
        sol[i + (3 * j) + (3 * 3 * k)] = ((C0 * C[i][j][k]) + (C1 * ((((C[i + 1][j][k] + C[i - 1][j][k]) + (C[i][j + 1][k] + C[i][j - 1][k])) + (C[i][j][k + 1] + C[i][j][k - 1]))))) / (C0 + C1);
      }
    }
  }
//#pragma endscop
}