
Configure storage for A
#pragma ACCEL PIPELINE auto{off}
  for (c_row = 0; c_row < 4; c_row++) {
    for (c_col = 0; c_col < 4; c_col++) {
      tmp = 0.0;
      coef = 1.0;
      for (a_row = 0; a_row < 4; a_row++) {
        tmp += coef * A[a_row][c_col] * B[c_row][a_row];
        coef = A[a_row][c_col];
      }
      C[c_row][c_col] = tmp;
    }
  }
// Matrix multiplication for 2 matrices with dim = 4
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (c_row = 0; c_row < 4; c_row++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c_col = 0; c_col < 4; c_col++) {
      tmp = C[c_row][c_col];
      total = 0.0;
      
#pragma ACCEL PARALLEL reduction=total FACTOR=auto{__PARA__L2}
      for (a_row = 0; a_row < 4; a_row++) {
        total += tmp * A[a_row][c_col] * B[a_row][c_row];
      }
      C[c_row][c_col] = total;
    }
  }
}
