#pragma ACCEL kernel

void kernel_mvt(int tsteps,int n,double A[40][30],double x1[40],double x2[30],double y1[40],double y2[30])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PARALLEL reduction = x1 FACTOR=auto{1}
    for (i = 0; i <= 29; i++) {
      x1[i] += + A[t][i] * y1[t];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PARALLEL reduction = x2 FACTOR=auto{10}
    for (i = 0; i <= 29; i++) {
      x2[i] += + A[t][i] * y2[t];
    }
  }
//#pragma endscop
}