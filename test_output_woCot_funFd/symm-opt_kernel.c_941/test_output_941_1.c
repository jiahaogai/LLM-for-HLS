Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{2}
Code: #pragma ACCEL PARALLEL FACTOR=auto{15}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{2}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
 #pragma ACCEL PARALLEL FACTOR=auto{15}

double alpha=1.0;
 double beta=2.0;
int i;
int j;
int k;
 double C[60][80];
 double A[60][60];
 double B[60][80];
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
      for (j = 0; j < 80; j++) {
        C[i][j] += alpha * A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}