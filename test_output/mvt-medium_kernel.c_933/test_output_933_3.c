#pragma ACCEL kernel

void kernel_mvt(int ni,int nj,int nk,double A[400][400],double x1[400],double x2[400],double y1[400],double y2[400])
{
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    y1[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{5}
    for (k = 0; k < 400; k++) {
      y1[i] += A[i][k] * x2[k];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{12}
  for (i = 0; i < 400; i++) {
    x2[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{120}
  for (i = 0; i < 400; i++) {
    y2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
    for (k = 0; k < 400; k++) {
      x2[i] += A[k][i] * y1[k];
    }
  }
//#pragma endscop
}