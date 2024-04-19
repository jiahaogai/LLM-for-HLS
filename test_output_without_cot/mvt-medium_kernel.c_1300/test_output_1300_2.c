9. `#pragma ACCEL PIPELINE auto{__PIPE__L2}`: Automatically pipeline the loop with pipeline auto{__PIPE__L2}.
10. `#pragma ACCEL TILE FACTOR=auto{__TILE__L2}`: Tile the loop with tile auto{__TILE__L2}.
11. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}`: Execute loop iterations concurrently with the specified parallelization factor.
12. `#pragma ACCEL PIPELINE auto{__PIPE__L3}`: Automatically pipeline the loop with pipeline auto{__PIPE__L3}.
13. `#pragma ACCEL TILE FACTOR=auto{__TILE__L3}`: Tile the loop with tile auto{__TILE__L3}.
14. `#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}`: Execute loop iterations concurrently with the specified parallelization factor.

### Original Kernel
 
#pragma ACCEL kernel

void kernel_mvt(double x1[400], double x2[400], double y_1[400], double y_2[400], double A[400][400])
{
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    x1[i] = 0.0;
    x2[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      x1[i] += A[i][j] * y_1[j];
    }
    
#pragma ACCEL PARALLEL reduction FACTOR=auto{__PARA__L2}
    for (j = 0; j < 400; j++) {
      x2[i] += A[i][j] * y_2[j];
    }
  }
//#pragma endscop
}