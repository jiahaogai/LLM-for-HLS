#pragma ACCEL kernel

void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = 0.0;
    double sum2 = 0.0;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * y_1[j];
    }
	x1[i] = sum;
	
#pragma ACCEL PARALLEL reduction=sum2 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      sum2 += A[i][j] * y_2[j];
    }
	x2[i] = sum2;
  }
}