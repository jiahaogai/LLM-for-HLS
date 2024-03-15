#pragma ACCEL kernel

void kernel_seidel_2d(int orig_A[25][20],int sol[25][20])
{
  int r;
  int c;
  int k;
  int j;
  int i;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (r = 0; r < 25; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    for (k = 1; k < 25; k++) {
      j = 0;
      i = 0;
      i = ((int )((short )r)) * 20;
      j = ((int )((short )k)) * 20;
      sol[r][k] = orig_A[r][k];
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      for (c = 0; c < 20; c++) {
        if (c != j) {
          sol[r][k] = sol[r][k] - orig_A[r][c] * ((double )(orig_A[r][j] / orig_A[j][j]));
        }
      }
    }
  }
}