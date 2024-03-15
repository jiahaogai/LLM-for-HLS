
  #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (tj = 0; tj < 40; tj++) {
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (ti = 0; ti < 40; ti++) {
      Model_Col_Dump = 0.0;
      Model_Row_Dump = 0.0;
      pad_col_idx = ti*5;
      pad_row_idx = tj*5;
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (i = 0; i < 3; i++) {
        pad_i = i + pad_row_idx;
        cols = 0;
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
        for (j = 0; j < 3; j++) {
          pad_j = j + pad_col_idx;
          cols = cols + orig[pad_i][pad_j] * k[i][j];
        }
        Model_Row_Dump += cols;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (i = 0; i < 3; i++) {
        pad_i = i + pad_row_idx;
        cols = 0;
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
        for (j = 0; j < 3; j++) {
          pad_j = j + pad_col_idx;
          cols = cols + Model_Row_Dump[j] * a[i][j];
        }
        Model_Col_Dump += cols;
      }
      pad_row_idx_idx = tj*40;
      pad_col_idx_idx = ti*40;
      out[pad_row_idx_idx][pad_col_idx_idx] = Model_Col_Dump;
    }
  }
}
