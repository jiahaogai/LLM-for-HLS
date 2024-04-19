#pragma ACCEL kernel

void kernel_mvt(int tsteps,int n,double A[40][50],double x1[40],double x2[50],double y_1[40],double y_2[50])
{
  int t;
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t <= 39; t++) {
    
#pragma ACCEL PARALLEL reduction=y_1 FACTOR=auto{__PARA__L2}
    for (i = 0; i <= 39; i++) {
      y_1[i] += A[i][t] * x1[t];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (t = 0; t <= 49; t++) {
    
#pragma ACCEL PARALLEL reduction=y_2 FACTOR=auto{__PARA__L3}
    for (j = 0; j <= 49; j++) {
      y_2[j] += A[t][j] * x2[t];
    }
  }
//#pragma endscop
}