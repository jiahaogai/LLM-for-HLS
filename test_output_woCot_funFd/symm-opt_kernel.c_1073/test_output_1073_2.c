#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (k_col = 0; k_col < 80; k_col++) {
        double temp2 = 0.0;
        int j_col;
        
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L2}
        for (j_col = 0; j_col < 60; j_col++) {
          mult = A[i][j_col] * B[j_col][k];
          temp2 += mult;
        }
	C[i][k] += temp2;
      }
    }
  }
}