#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[20][30],double A[20][40],double B[40][30],double D[20][30])
{
  int i;
  int j;
  int k;
//#pragma scop
/* D := alpha*A*B*C + beta*D */
  
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
      D[i][j] = alpha * tmp + beta * C[i][j];
    }
  }
//#pragma endscop
}