#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[200][220],double A[200][200],double B[200][200],double tmp[200][200],double D[200][220])
{
  int i;
  int j;
  int k;
//#pragma scop
/* D := alpha*A*B*C + beta*D */
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 220; j++) {
      double tmp_ij = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp_ij FACTOR=auto{32}
      for (k = 0; k < 200; k++) {
        tmp_ij += alpha * A[i][k] * B[k][j];
      }
      D[i][j] = beta * D[i][j] + tmp_ij;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 200; j++) {
      double tmp_ij = 0.0;
      
#pragma ACCEL PARALLEL reduction=tmp_ij FACTOR=auto{32}
      for (k = 0; k < 200; k++) {
        tmp_ij += A[i][k] * C[k][j];
      }
      tmp[i][j] = tmp_ij;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 0; j < 220; j++) {
      D[i][j] = beta * D[i][j] + alpha * tmp[i][j] * D[j][j];
    }
  }
//#pragma endscop
}