#pragma ACCEL kernel

void kernel_mvt(int tsteps,int n,double A[40][50],double x[50],double y[40],double tmp[40])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 39; t++) {
    tmp[t] = 0.0;
    y[t] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (i = 0; i <= 49; i++) {
      tmp[t] = A[t][i] * x[i];
      y[t] += tmp[t];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 39; t++) {
    y[t] = y[t] + 1.0;
  }
//#pragma endscop
}