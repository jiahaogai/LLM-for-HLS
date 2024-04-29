#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[200][220],double A[200][200],double B[220][200])
{
  int i;
  int j;
  int k;
  int k_col;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{60}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 220; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 200; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
      for (k_col = 0; k_col < 200; k_col++) {
        mult = alpha * A[k][k_col];
        
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
        for (j = 0; j < 200; j++) {
          C[i][j] += mult * B[k_col][j];
        }
      }
    }
  }
}