 You have 40000000 elements in each array. After the above kernel has been applied, the results should match with the reference data. 
 #pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double tmp[400][500],double A[400][700],double B[700][800],double C[500][800],double D[400][800])
{
  int i;
  int j;
  int k;
//#pragma scop
/* D := alpha*A*B*C + beta*D */
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 500; j++) {
      tmp[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{8}
      for (k = 0; k < 700; ++k) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 800; j++) {
      D[i][j] *= beta;
      
#pragma ACCEL PARALLEL reduction=D FACTOR=auto{2}
      for (k = 0; k < 500; ++k) {
        D[i][j] += tmp[i][k] * C[k][j];
      }
    }
  }
//#pragma endscop
}
