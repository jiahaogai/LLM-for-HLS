#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double vec1[400],double vec2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    vec1[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=vec1 FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * vec2[j];
    }
    vec1[i] = tmp;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 400; i++) {
    double tmp = 0.0;
    vec2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=vec2 FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      tmp += A[i][j] * vec1[j];
    }
    vec2[i] = tmp;
  }
}