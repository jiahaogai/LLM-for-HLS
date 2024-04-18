#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double vec1[400],double vec2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    vec1[i] = 0.0;
    for (j = 0; j < 400; j++) {
      vec1[i] += A[i][j] * vec2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    vec2[i] = 0.0;
    for (j = 0; j < 400; j++) {
      vec2[i] += A[i][j] * vec1[j];
    }
  }
}