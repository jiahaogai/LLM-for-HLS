#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,int nm,double E[40][50],double A[40][60],double B[60][50],double F[50][70],double C[50][80],double D[80][70],double G[40][70])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    for (j = 0; j < 50; j++) {
      E[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=E FACTOR=auto{__PARA__L2}
      for (k = 0; k < 60; ++k) {
        E[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    for (j = 0; j < 70; j++) {
      F[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=F FACTOR=auto{__PARA__L5}
      for (k = 0; k < 50; ++k) {
        F[i][j] += E[i][k] * C[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L6}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L6}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L7}
    for (j = 0; j < 80; j++) {
      G[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=G FACTOR=auto{__PARA__L8}
      for (k = 0; k < 60; ++k) {
        G[i][j] += F[k][j] * D[k][i];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L9}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L9}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L10}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L10}
    for (j = 0; j < 70; j++) {
      double sum_tmp = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum_tmp FACTOR=auto{__PARA__L11}
      for (k = 0; k < 50; ++k) {
        sum_tmp += G[k][j] * A[i][k];
      }
      C4[i][j] = sum_tmp;
    }
  }
//#pragma endscop
}