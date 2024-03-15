
8. Set the following options:
	A0 = 1
	B0 = 1
	C0 = 1
	P0 = 2
	Q0 = 2
	R0 = 2
	S0 = 256
	T0 = 256
	A = 1
	B = 256
	C = 256
	P = 4
	Q = 4
	R = 4
	S = 8
	T = 8

 #pragma ACCEL kernel

void kernel_doitgen(int ni,int nj,int nk,int nl,int nm,double E[40][50],double A[40][60],double B[60][50],double F[50][70],double C[50][80],double D[80][70])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      A[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 50; j++) {
      E[i][j] = 0.0;
      
#pragma ACCEL PARALLEL reduction=E FACTOR=auto{1}
      for (k = 0; k < 30; k++) {
        E[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 70; j++) {
      F[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 50; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 70; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 30; k++) {
        F[i][j] += C[i][k] * D[k][j];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 70; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = 0; k < 30; k++) {
        A[i][k] += E[i][j] * F[j][k];
      }
    }
  }
//#pragma endscop
}
