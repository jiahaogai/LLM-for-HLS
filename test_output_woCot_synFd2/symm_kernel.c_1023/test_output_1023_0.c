#pragma ACCEL kernel

void kernel_symm(int ni,int nj,int nk,double alpha,double beta,double C[200][220],double A[200][240],double B[240][220])
{
  int i;
  int j;
  int k;
  double temp_x;
  double temp_y;
  double mul;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 220; j++) {
      temp_x = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp_x FACTOR=auto{4}
      for (k = 0; k < 240; ++k) {
        temp_y = A[i][k] * B[k][j];
        mul = alpha * temp_y;
        temp_x += mul;
      }
      C[i][j] = beta * C[i][j] + temp_x;
    }
  }
}