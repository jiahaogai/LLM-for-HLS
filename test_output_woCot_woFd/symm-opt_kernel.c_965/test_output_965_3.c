#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{4}
      for (j = 0; j < 80; j++) {
        k_col = 0;
        double temp_1 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp_1 FACTOR=auto{2}
	for (k_col = 0; k_col < 60; k_col++) {
          mult = A[k][k_col] * B[k_col][j];
          temp_1 += mult;
        }
	C[i][j] += temp_1;
      }
    }
  }
}