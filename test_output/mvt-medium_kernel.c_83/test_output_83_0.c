#pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double vec1[400],double vec2[400])
{
  int i;
  int j;
  double temp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    temp = 0.0;
    
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      temp += A[i][j] * vec1[j];
    }
    vec2[i] = temp;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 400; i++) {
    temp = 0.0;
    
#pragma ACCEL PARALLEL reduction=temp FACTOR=auto{__PARA__L3}
    for (j = 0; j < 400; j++) {
      temp += A[j][i] * vec2[j];
    }
    vec1[i] = temp;
  }
}