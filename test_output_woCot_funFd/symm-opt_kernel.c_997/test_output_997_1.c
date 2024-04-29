Code: #pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double tmp;
  double mult;
  double sum = 0.0;
  double tmp_x;
  double tmp_y;
  double tmp2 = 0.0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 80; j++) {
      tmp_x = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp_x FACTOR=auto{1}
      inner:
      for (k = 0; k < 60; k++) {
        k_col = 60 * k + j;
        tmp = A[i][k];
        mult = tmp * B[k][k_col];
        tmp_x += mult;
      }
      tmp_y = C[i][j] * alpha;
      tmp2 += tmp_x + tmp_y;
    }
    C[i][tmp_x.index] = tmp2 * beta;
    tmp2 = 0.0;
  }
}