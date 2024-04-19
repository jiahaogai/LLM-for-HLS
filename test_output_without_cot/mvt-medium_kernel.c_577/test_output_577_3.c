#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
   for (i = 0; i < 400; i++) {
      tmp = y_1[i] * A[i][0];
      x1[0] += A[i][0] * y_1[i];
      x1[1] += A[i][1] * y_1[i];
      x1[2] += A[i][2] * y_1[i];
      x1[3] += A[i][3] * y_1[i];
      x1[4] += A[i][4] * y_1[i];
      x2[0] += A[i][0] * y_2[i];
      x2[1] += A[i][1] * y_2[i];
      x2[2] += A[i][2] * y_2[i];
      x2[3] += A[i][3] * y_2[i];
      x2[4] += A[i][4] * y_2[i];
    }