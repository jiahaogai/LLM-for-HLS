#pragma ACCEL kernel

void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
{
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    x1[i] = 0.0;
    x2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{3}
    for (j = 0; j < 400; j++) {
      x1[i] = x1[i] + A[i][j] * y_1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 400; i++) {
    y_2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{3}
    for (j = 0; j < 400; j++) {
      y_2[i] = y_2[i] + A[i][j] * x2[j];
    }
  }
//#pragma endscop
}