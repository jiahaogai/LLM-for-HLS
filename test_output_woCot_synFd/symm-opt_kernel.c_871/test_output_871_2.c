#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{60}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        int temp2;
        k_col = 0;
        mult = alpha * A[k][k_col];
        temp2 = (int )(mult * B[k][j] + 0.5);
        C[i][j] += temp2;
        k_col++;
      }
    }
  }
}