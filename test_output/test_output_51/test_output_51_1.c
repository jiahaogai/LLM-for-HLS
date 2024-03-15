
 #pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[20][22],double B[20][24],double C[24][22],double D[24][30])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    for (j = 0; j < 22; j++) {
      A[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    for (j = 0; j < 24; j++) {
      B[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 24; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    for (j = 0; j < 22; j++) {
      C[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 24; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L5}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L5}
    for (j = 0; j < 30; j++) {
      D[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 20; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L6}
    for (j = 0; j < 24; j++) {
      for (k = 0; k < 20; k++) {
        A[i][j] += B[i][k] * C[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 24; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L7}
    for (j = 0; j < 22; j++) {
      for (k = 0; k < 20; k++) {
        D[i][j] += A[k][j] * B[k][i];
      }
    }
  }
//#pragma endscop
}
