
5. This loop is parallelized auto-1
   #pragma ACCEL PIPELINE auto{__PIPE__L4}
   #pragma ACCEL TILE FACTOR=auto{__TILE__L4}
   #pragma ACCEL PARALLEL FACTOR=auto{32}
	for (j = 1; j < 32; j++) {
    tmp = A[i][0] * B[0][j] +A[i][1] * B[1][j] +A[i][2] * B[2][j] +A[i][3] * B[3][j] +A[i][4] * B[4][j];
    C[i][j] = tmp;
  }

6. This loop is parallelized auto{__PARA__L2}
   #pragma ACCEL PIPELINE auto{__PIPE__L2}
   #pragma ACCEL TILE FACTOR=auto{__TILE__L2}
   #pragma ACCEL PARALLEL FACTOR=auto{1}
	for (i = 1; i < 20; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 32; j++) {
      A[i][j] = A[i][j] + 1.0;
    }
  }

7. This loop is parallelized auto{__PARA__L1}
   #pragma ACCEL PIPELINE auto{__PIPE__L1}
   #pragma ACCEL TILE FACTOR=auto{__TILE__L1}
   #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
	for (i = 0; i < 20; i++) {
    B[i][0] = A[i][0] * B[i][0];
  }

