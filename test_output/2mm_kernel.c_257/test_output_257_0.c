#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[40][80],double A[40][60],double B[60][80],double tmp[40][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      tmp[i][j] = 0.0;
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{__PARA__L3}
      for (j = 0; j < 80; j++) {
        tmp[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C[i][j] FACTOR=auto{__PARA__L5}
      for (j = 0; j < 80; j++) {
        C[i][j] += beta * tmp[i][j] * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}