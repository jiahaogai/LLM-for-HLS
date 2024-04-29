#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{10}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        k_col = k * 80;
        mult = alpha * A[i][k] * B[k][j];
        temp2[0] = C[i][j_col + 0] + mult;
        temp2[1] = C[i][j_col + 1] + mult;
        temp2[2] = C[i][j_col + 2] + mult;
        temp2[3] = C[i][j_col + 3] + mult;
        temp2[4] = C[i][j_col + 4] + mult;
        temp2[5] = C[i][j_col + 5] + mult;
        temp2[6] = C[i][j_col + 6] + mult;
        temp2[7] = C[i][j_col + 7] + mult;
        C[i][j_col + 0] = temp2[0];
        C[i][j_col + 1] = temp2[1];
        C[i][j_col + 2] = temp2[2];
        C[i][j_col + 3] = temp2[3];
        C[i][j_col + 4] = temp2[4];
        C[i][j_col + 5] = temp2[5];
        C[i][j_col + 6] = temp2[6];
        C[i][j_col + 7] = temp2[7];
      }
    }
  }
}