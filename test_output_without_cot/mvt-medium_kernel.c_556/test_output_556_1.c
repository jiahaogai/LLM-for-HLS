9. '#pragma ACCEL PIPELINE auto{__PIPE__L2}' - Automatically pipeline this loop with pipeline auto{__PIPE__L2}.

10. '#pragma ACCEL TILE FACTOR=auto{__TILE__L2}' - Automatically tile this loop with tile auto{__TILE__L2}.

11. '#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}' - Execute loop iterations in parallel with an automatically determined parallel factor.

12. '#pragma ACCEL PIPELINE auto{__PIPE__L3}' - Automatically pipeline this loop with pipeline auto{__PIPE__L3}.

13. '#pragma ACCEL TILE FACTOR=auto{__TILE__L3}' - Automatically tile this loop with tile auto{__TILE__L3}.

14. '#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}' - Execute loop iterations in parallel with an automatically determined parallel factor.

 #pragma ACCEL kernel

void kernel_mvt(int n,double A[400][400],double x1[400],double x2[400],double y_1[400],double y_2[400])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 400; i++) {
    y_1[i] = ((double )0);
    y_2[i] = 0.0;
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{12}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      y_1[i] += A[j][i] * x1[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 400; i++) {
    for (j = 0; j < 400; j++) {
      y_2[i] += A[i][j] * x2[j];
    }
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L3}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 400; i++) {
    x1[i] = y_1[i] + y_2[i];
  }
}