#pragma ACCEL kernel

void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
{
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = y_1[i];
    
#pragma ACCEL PARALLEL reduction=x1 FACTOR=auto{8}
    for (j = 0; j < 400; j++) {
      x1[j] += tmp * A[i][j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = y_2[i];
    
#pragma ACCEL PARALLEL reduction=x2 FACTOR=auto{16}
    for (j = 0; j < 400; j++) {
      x2[j] += tmp * A[i][j];
    }
  }
//#pragma endscop
}