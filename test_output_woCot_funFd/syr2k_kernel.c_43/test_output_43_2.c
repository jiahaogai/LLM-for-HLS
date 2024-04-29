Code: #pragma ACCEL kernel

void kernel_syrk(double alpha,double beta,double C[80][80],double A[80][60])
{
  int i;
  int j;
  int k;
  double mult;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 80; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = i; j < 80; j++) {
      mult = 0.0;
      
#pragma ACCEL PARALLEL reduction=mult FACTOR=auto{8}
      for (k = 0; k < 60; k++) {
        mult += A[i][k] * A[j][k];
      }
      C[i][j] += mult * alpha;
      C[j][i] += mult * alpha;
    }
    C[i][i] *= beta;
  }
}