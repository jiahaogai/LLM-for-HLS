#pragma ACCEL kernel

void kernel_symm(int ni,int nj,int nk,double alpha,double beta,double C[200][220],double A[200][200],double B[200][220])
{
  int i;
  int j;
  int k;
  double temp_x;
  double mul;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 220; j++) {
      temp_x = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 200; k++) {
        mul = alpha * A[i][k] * B[k][j];
        temp_x += mul;
      }
      C[i][j] = temp_x + beta * C[i][j];
    }
  }
}