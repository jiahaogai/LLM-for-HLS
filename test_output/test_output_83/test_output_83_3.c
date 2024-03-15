
 #pragma ACCEL kernel

void kernel_doit(double A[250][250],double C4[250][250],double sum[250])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    double tmp = 0.0;
    
#pragma ACCEL PIPELINE auto{off}
    for (k = 0; k < 250; k++) {
      tmp += A[i][k] * C4[k][i];
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 250; j++) {
      C4[i][j] = A[i][j] * tmp;
    }
    sum[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 250; i++) {
    for (j = 0; j < 250; j++) {
      sum[i] += C4[i][j];
    }
  }
//#pragma endscop
}
