Code: ### Parameters

**alpha**: double 

**beta**: double 

**C**: double[80][80]

**A**: double[80][60]

**B**: double[80][60]

### Local Variables
  
#pragma ACCEL PIPELINE auto{off}  
  
#pragma ACCEL TILE FACTOR=auto{1}  
  
#pragma ACCEL PARALLEL FACTOR=auto{16}  
  double C_rowsum;
  
#pragma ACCEL PIPELINE auto{}  
  
#pragma ACCEL TILE FACTOR=auto{1}  
  
#pragma ACCEL PARALLEL FACTOR=auto{2}  
  double B_colsum;
  
#pragma ACCEL PIPELINE auto{}  
  
#pragma ACCEL TILE FACTOR=auto{1}  
  
#pragma ACCEL PARALLEL FACTOR=auto{8}  
  int i;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}  
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{4}  
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}  
  
#pragma ACCEL TILE FACTOR=auto{1}  
  
#pragma ACCEL PARALLEL FACTOR=auto{1}  
  for (j = 0; j < 80; j++) {
    C_rowsum = 0.0;
    
#pragma ACCEL PARALLEL reduction=C_rowsum FACTOR=auto{16}  
    for (i = 0; i < 60; i++) {
      C_rowsum += C[j][i] * A[j][i];
    }
    
#pragma ACCEL PARALLEL reduction=C_rowsum FACTOR=auto{16}  
    for (k = 0; k < 60; k++) {
      C_rowsum += C[j][k] * B[k][j];
    }
    C[j][j] = C_rowsum;
  }
//Blas scaling
  
#pragma ACCEL PARALLEL FACTOR=auto{1}  
  for (i = 0; i < 80; i++) {
    C[i][i] *= beta;
  }
//Factorization
  
#pragma ACCEL PIPELINE auto{off}  
  
#pragma ACCEL TILE FACTOR=auto{1}  
  
#pragma ACCEL PARALLEL FACTOR=auto{1}  
  for (j = 0; j < 80 - 1; j++) {
    B_colsum = 0.0;
    
#pragma ACCEL PARALLEL reduction=B_colsum FACTOR=auto{1}  
    for (k = 0; k < 60; k++) {
      B_colsum += B[k][j] * A[k][j];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}  
    for (i = 0; i < 60; i++) {
      C[i][j + 1] += alpha * B[i][j] * B_colsum;
    }
  }
//#pragma endscop
}