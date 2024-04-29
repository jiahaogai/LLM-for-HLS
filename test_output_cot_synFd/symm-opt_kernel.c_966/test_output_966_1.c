#pragma ACCEL kernel 

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{20}
 void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[80][60])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{80}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{12}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{12}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      double temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L2}
      double temp1 = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (j = 0; j < 60; j++) {
        mult = alpha * A[i][j] * B[j][k];
        temp1 += mult;
        temp2 += mult * C[j][k];
      }
      C[i][k] = temp1 + temp2;
    }
  }
}