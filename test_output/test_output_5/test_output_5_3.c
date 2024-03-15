

5. Do not pipeline the loop below: #pragma ACCEL PIPELINE auto{off}
  
6. Do not parallelize the loop below: #pragma ACCEL PARALLEL auto{1}
  
7. #pragma ACCEL PIPELINE auto{__PIPE__L2}
  
8. #pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
9. #pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (tiled_index = 0; tiled_index < 8; tiled_index++) {
    int _in_j = 0;
    int _in_j_col = (((int )tiled_index) * 64) + 1;
    int _in_j_row = 1;
    int _out_j = 0;
    int _out_j_col = (((int )tiled_index) * 64) + 1;
    int _out_j_row = 1;
    for (j_col = 1; j_col <= 60; j_col += 64) {
      if (j_col + 64 - 1 < 60) {
        _in_j_col = j_col + 64 - 1;
      }
      else {
        _in_j_col = 60;
      }
      for (j_row = 1; j_row <= 60; j_row += 64) {
        if (j_row + 64 - 1 < 60) {
          _in_j_row = j_row + 64 - 1;
        }
        else {
          _in_j_row = 60;
        }
//#pragma ACCEL PIPELINE auto{off}
        for (in_j = 0; in_j <= 79; in_j++) {
          _in = in[in_j][_in_j_row][_in_j_col];
//#pragma ACCEL PARALLEL reduction=out FACTOR=auto{__PARA__L2}
          for (out_j = 0; out_j <= 79; out_j++) {
            out[out_j][_out_j_row][_out_j_col] += _in * A[out_j][in_j];
          }
        }
//#pragma ACCEL PIPELINE auto{__PIPE__L2}
      }
//#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    }
//#pragma ACCEL PIPELINE auto{__PIPE__L1}
  }
//#pragma ACCEL PIPELINE auto{off}

  }
