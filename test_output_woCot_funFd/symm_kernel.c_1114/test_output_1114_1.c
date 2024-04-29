C := alpha*A*B + beta*C,

A is M (row) x M (column)

B is M (row) x N (column)

C is M (row) x N (column)
int M;
int N;
int P;
double alpha;
double beta;
double C[60][80];
double A[60][60];
double B[60][80];
  
#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
for (int i = 0; i < 60; i++) {
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (int j = 0; j < 80; j++) {
    C[i][j] *= beta;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{20}
  for (int j = 0; j < 60; j++) {
    
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{4}
    for (int k = 0; k < 60; ++k) {
      double temp2 = 0.0;
      
#pragma ACCEL PARALLEL reduction=temp1 FACTOR=auto{1}
      for (int l = 0; l < 80; ++l) {
        temp1[0] = A[i][k] * B[k][l];
        temp2 += temp1[0];
      }
      C[i][l] += temp2;
    }
  }
}
  
#pragma endscop
}