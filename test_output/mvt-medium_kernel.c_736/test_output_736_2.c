#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,int nk,double A[200][220],double B[200][240],double x[240],double y[220])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 220; i++) {
    
#pragma ACCEL PARALLEL reduction=y FACTOR=auto{10}
    for (j = 0; j < 200; j++) {
      y[i] += A[j][i] * x[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{30}
  for (i = 0; i < 200; i++) {
    
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{5}
    for (j = 0; j < 240; j++) {
      x[j] += B[i][j] * y[i];
    }
  }
//#pragma endscop
}