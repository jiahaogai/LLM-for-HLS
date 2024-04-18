#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[20][30],double A[20][40],double B[40][30],double D[20][30])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 30; j++) {
      double tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{14}
      for (k = 0; k < 40; ++k) {
        tmp += A[i][k] * B[k][j];
      }
      D[i][j] = tmp;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PIPELINE auto{auto{__PIPE__L2}}
    
#pragma ACCEL TILE FACTOR=auto{auto{__TILE__L2}}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 30; j++) {
      double tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (k = 0; k < 40; ++k) {
        tmp += D[k][j] * A[i][k];
      }
      C[i][j] = beta * C[i][j] + alpha * tmp;
    }
  }
//#pragma endscop
}