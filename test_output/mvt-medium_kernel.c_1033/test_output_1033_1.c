#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double vec1[400],double vec2[400],double out1[400],double out2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    out1[i] = 0.0;
    vec1[i] = 0.0;
    for (j = 0; j < 400; j++) {
      vec1[i] += A[i][j] * out2[j];
    }
    out1[i] = vec1[i] + 1.0;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  for (i = 0; i < 400; i++) {
    out2[i] = 0.0;
    vec2[i] = 0.0;
    for (j = 0; j < 400; j++) {
      vec2[i] += A[i][j] * out1[j];
    }
    out2[i] = vec2[i] + 1.0;
  }
}