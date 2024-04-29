Code: #pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{60}

#pragma ACCEL PARALLEL FACTOR=auto{1}

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{20}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L1}
        for (auto l = 0; l < 60; l++) {
          double temp1 = A[i][l] * B[l][j];
          temp2 += temp1;
        }
        C[i][j] += alpha * temp2;
      }
    }
  }
}