#pragma ACCEL kernel

void kernel_mvt(int tsteps,int n,double A[400][400],double x1[400],double x2[400],double y_1[400],double y_2[400])
{
  int t;
  int i;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 400; t++) {
    
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{__PARA__L2}
    for (i = 0; i < 400; i++) {
      x1[i] = A[i][t] * y_1[t];
    }
    
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{__PARA__L3}
    for (i = 0; i < 400; i++) {
      x2[i] = A[i][t] * y_2[t];
    }
  }
//#pragma endscop
}