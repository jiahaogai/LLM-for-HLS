#pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
#pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
#pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
#pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
#pragma ACCEL TILE FACTOR=auto{1}
Error: 
Please check the code and try again.
#pragma ACCEL PARALLEL FACTOR=auto{1}
Error: 
Please check the code and try again.
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{1}
Error: 
Please check the code and try again.
double alpha;
double beta;
double C[200][240];
double A[200][200];
double B[200][240];
double temp1[200][240];
double temp2[240];
int i;
int j;
int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction = temp2 FACTOR=auto{10}
  for (j = 0; j < 240; j++) {
    temp2[j] = 0.0;
    for (k = 0; k < 200; k++) {
      temp2[j] += A[i][k] * B[k][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 240; j++) {
    C[i][j] *= beta;
    C[i][j] += alpha * temp2[j];
  }
}
//#pragma endscop