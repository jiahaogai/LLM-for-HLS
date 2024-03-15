
 //
 //  TwoMM:  This program solves a system of linear
 //  equations of the form: A * X = B
 //
 //  A is an n x n matrix
 //  B is an n x m matrix
 //  X is an n x m matrix
 //
 
#pragma ACCEL kernel

void TwoMM(int n,int m,double A[40][40],double B[40][60],double X[40][60])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
    for (j = 0; j < 60; j++) {
      X[i][j] = ((double )0);
    }
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 40; i++) {
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      for (k = 0; k < 60; k++) {
        X[j][k] += A[i][j] * B[i][k];
      }
    }
  }
//#pragma endscop
}
