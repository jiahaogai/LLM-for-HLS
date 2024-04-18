#pragma ACCEL kernel

void kernel_2mm(int ni,int nj,int nk,int nl,double alpha,double beta,double C[200][220],double A[200][200],double B[200][220],double D[200][240])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{32}
    for (j = 0; j < 220; j++) {
      A[i][j] += 1.0;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{32}
    for (j = 0; j < 240; j++) {
      B[i][j] += 1.0;
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
    for (j = 0; j < 220; j++) {
      
#pragma ACCEL PARALLEL reduction=D FACTOR=auto{__PARA__L3}
      for (k = 0; k < 200; k++) {
        D[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{__PARA__L5}
    for (j = 0; j < 240; j++) {
      C[i][j] += beta * D[i][j];
    }
  }
//#pragma endscop
}