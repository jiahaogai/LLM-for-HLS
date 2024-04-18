#pragma ACCEL kernel

void kernel_mvt(int tsteps,int n,double A[400][400],double x1[400],double x2[400],double y1[400],double y2[400])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t <= 399; t++) {
    
#pragma ACCEL PARALLEL reduction = x1 FACTOR=auto{10}
    for (i = 0; i <= 399; i++) {
      x1[i] += y1[t] * A[i][t];
    }
    
#pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{10}
    for (j = 0; j <= 399; j++) {
      x2[j] += y2[t] * A[t][j];
    }
  }
//#pragma endscop
}