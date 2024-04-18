c
 #pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  kernel_vmv:
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    int jj;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{30}
    kernel_vmv_vmv_1:
    for (jj = 0; jj < 400; jj++) {
      sum += A[i][jj] * y_1[jj];
    }

    x1[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  kernel_smv:
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    int ij;
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{24}
    kernel_smv_smv_1:
    for (ij = 0; ij < 400; ij++) {
      sum += A[ij][i] * y_2[ij];
    }

    x2[i] = sum;
  }
}