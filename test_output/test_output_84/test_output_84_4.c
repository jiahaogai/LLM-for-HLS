
 #pragma ACCEL kernel

void kernel_atax(double A[340],double x[420],double y[420],int idx[420])
{
  int i;
  int j;
  double tmp;
  double si;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  y[0] = 0.0;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 420; i++) {
    tmp = 0.0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{32}
    for (j = 0; j < 340; j++) {
      tmp += A[j * 420] * x[j * 420];
    }
    si = tmp / (1.0 + 1.0);
    y[i] = si;
    j = 0;
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{32}
    for (j = 0; j < 340; j++) {
      y[i] += A[j * 420] * x[j];
    }
  }
}
