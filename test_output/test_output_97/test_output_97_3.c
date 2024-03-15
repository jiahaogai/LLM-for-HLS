 
 #pragma ACCEL kernel

void kernel_atax(double A[340][420],double x[420],double y[420],double tmp[340])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 420; i++) {
    tmp[0] = A[0][i] * x[i];
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 420; i++) {
    y[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 340; j++) {
      y[i] += tmp[j] * A[j][i];
    }
  }
}
