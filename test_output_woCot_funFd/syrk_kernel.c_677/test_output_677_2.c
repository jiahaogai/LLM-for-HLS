Code: #pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
 
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  double kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (j = 0; j < 80; j++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
    for (i = 0; i < 80; i++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{70}
      for (j = 0; j < 80; j++) {
        mult = alpha * A[i][k];
        C[i][j] += mult * A[j][k];
      }
    }
  }
  return 0.0;
}