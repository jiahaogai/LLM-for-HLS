#pragma ACCEL kernel

void kernel_mvt(int tsteps,int n,double A[400][400],double x1[400],double x2[400],double y_1[400],double y_2[400])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 399; t++) {
    
#pragma ACCEL PARALLEL reduction = x1 FACTOR=auto{1}
    for (i = 0; i <= 399; i++) {
      x1[i] += + A[i][t] * y_1[t];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{24}
  for (t = 0; t <= 399; t++) {
    
#pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{10}
    for (i = 0; i <= 399; i++) {
      x2[i] += + A[i][t] * y_2[t];
    }
  }
//#pragma endscop
}