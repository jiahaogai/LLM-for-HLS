#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{8}

double kernel_trmm(double alpha,double A[60][60],double B[60][80])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{80}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL reduction=A FACTOR=auto{4}
    for (j = 0; j < 60; j++) {
      A[i][j] *= alpha;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (k = 0; k < 60; k++) {
      
#pragma ACCEL PARALLEL reduction=B FACTOR=auto{60}
      for (j = 0; j < 80; j++) {
        B[i][j] += A[i][k] * B[k][j];
      }
    }
  }
//#pragma endscop
}