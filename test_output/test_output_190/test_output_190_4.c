

  int i;
  int j;
  int k;j = 1;
  int tmp;tmp = 1;
  int SQUARE_DIM;SQUARE_DIM = 12;
  int INIT_VAL;INIT_VAL = 1;
  
#pragma ACCEL kernel

  kernel_heat_3d(i,j,tmp,SQUARE_DIM):
  for(i = 1; i < 12 - 1; i++) {
    for(j = 1; j < 12 - 1; j++) {
      C[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[i - 1][j] + A[1 + i][j]);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 12 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 12 - 1; j++) {
      C[i][j] = 0.2 * (A[i][j] + A[i][j - 1] + A[i][1 + j] + A[i - 1][j] + A[1 + i][j]);
    }
  }
}
