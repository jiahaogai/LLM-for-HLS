#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[40][80],double A[40][70],double B[70][50],double D[40][50])
{
  int i;
  int j;
  int k;
//#pragma scop
/* D := alpha*A*B*C + beta*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      double tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (k = 0; k < 50; k++) {
        tmp += alpha * A[i][k] * B[k][j];
      }
      C[i][j] = beta * D[i][j] + tmp;
    }
  }
/* end D := alpha*A*B*C + beta*D */
//#pragma endscop
}