#pragma ACCEL kernel

void kernel_symm(double alpha,double beta,double C[60][80],double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
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
      for (j = 0; j < 80; j++) {
        double temp2 = 0.0;
        
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L2}
        for (long long kindex = 0LL; kindex < 60LL; kindex += 20LL) {
          double temp1 = 0.0;
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{__PARA__L1}
          for (long long jindex = 0LL; jindex < 80LL; jindex += 4LL) {
            long long src_offset = kindex * 80LL + jindex;
            long long dst_offset = k * 80LL + jindex;
            temp1 += A[kindex][j] * B[dst_offset][src_offset];
          }
          temp2 += temp1;
        }
        C[i][j] += alpha * temp2;
      }
    }
  }
//#pragma endscop
}