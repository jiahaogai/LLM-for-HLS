#pragma ACCEL PIPELINE auto{}
Error: 
Please check the code and try again.
#pragma ACCEL TILE FACTOR=auto{2}
Error: 
Please check the code and try again.
#pragma ACCEL PARALLEL FACTOR=auto{16}
Error: 
Please check the code and try again.
double C[80][80];
double A[80][60];
double B[80][60];
int i;
int j;
int k;
double mult;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{16}
    for (j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=C FACTOR=auto{32}
      for (j = 0; j < 80; j++) {
        mult = alpha * A[i][k] * B[k][j];
        C[i][j] += mult;
      }
    }
  }
//#pragma endscop
}