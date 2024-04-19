#pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,double A[40][50],double B[50][40],double C[40][60],double D[60][50],double product[40][50])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 50; j++) {
      A[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 40; j++) {
      B[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      C[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      D[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 50; j++) {
      
#pragma ACCEL PARALLEL reduction=A{__PARA__L2}
      for (k = 0; k < 30; k++) {
        A[i][j] += B[j][k] * C[i][k];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    for (j = 0; j < 40; j++) {
      
#pragma ACCEL PARALLEL reduction=D{__PARA__L4}
      for (k = 0; k < 30; k++) {
        D[i][j] += A[j][k] * D[k][i];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      
#pragma ACCEL PARALLEL reduction=product{__PARA__L6}
      for (k = 0; k < 50; k++) {
        product[i][j] += A[i][k] * D[k][j];
      }
    }
  }
//#pragma endscop
}