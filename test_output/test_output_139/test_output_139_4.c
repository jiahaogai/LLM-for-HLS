
 #pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i <= 256; i++) {
     force_in_vec = 0.0;
     j_col_begin = 1L + (i - 1) * 256L;
     j_col_end = 1L + i * 256L;
     j_col_col = j_col_begin;
     force_in_row_begin = 1 + (j_col_begin - 1) * 256L;
     force_in_row_end = 1 + (j_col_end - 1) * 256L;
     force_in_row_row = force_in_row_begin;
     for (j = 1; j_col_col < j_col_end; j++) {
        j_col = j * 256L;
        tmp = 0.0;
        force_in_row = force_in_row_row;
        flm = 0.0;
        _in_off = 0;
        _col_off = j_col * 256L;
         _in_ptr =  _in_off +  _in_row_ptr;
         flm +=  _in_ptr[0] * 4.0;
        flm +=  _in_ptr[1] * 4.0;
        flm +=  _in_ptr[2] * 4.0;
        flm +=  _in_ptr[3] * 4.0;
        flm +=  _in_ptr[4] * 4.0;
        flm +=  _in_ptr[5] * 4.0;
        flm +=  _in_ptr[6] * 4.0;
        flm +=  _in_ptr[7] * 4.0;
        flm +=  _in_ptr[8] * 4.0;
        flm +=  _in_ptr[9] * 4.0;
        flm +=  _in_ptr[10] * 4.0;
        flm +=  _in_ptr[11] * 4.0;
        flm +=  _in_ptr[12] * 4.0;
        flm +=  _in_ptr[13] * 4.0;
        flm +=  _in_ptr[14] * 4.0;
        flm +=  _in_ptr[15] * 4.0;
        flm +=  _in_ptr[16] * 4.0;
        flm +=  _in_ptr[17] * 4.0;
        flm +=  _in_ptr[18] * 4.0;
        flm +=  _in_ptr[19] * 4.0;
        flm +=  _in_ptr[20] * 4.0;
        flm +=  _in_ptr[21] * 4.0;
        flm +=  _in_ptr[22] * 4.0;
        flm +=  _in_ptr[23] * 4.0;
        flm +=  _in_ptr[24] * 4.0;
        flm +=  _in_ptr[25] * 4.0;
        flm +=  _in_ptr[26] * 4.0;
        flm +=  _in_ptr[27] * 4.0;
        flm +=  _in_ptr[28] * 4.0;
        flm +=  _in_ptr[29] * 4.0;
        flm +=  _in_ptr[30] * 4.0;
        flm +=  _in_ptr[31] * 4.0;
        flm +=  _in_ptr[32] * 4.0;
        flm +=  _in_ptr[33] * 4.0;
        flm +=  _in_ptr[34] * 4.0;
        flm +=  _in_ptr[35] * 4.0;
        flm +=  _in_ptr[36] * 4.0;
        flm +=  _in_ptr[37] * 4.0;
        flm +=  _in_ptr[38] * 4.0;
        flm +=  _in_ptr[39] * 4.0;
        flm +=  _in_ptr[40] * 4.0;
        flm +=  _in_ptr[41] * 4.0;
        flm +=  _in_ptr[42] * 4.0;
        flm +=  _in_ptr[43] * 4.0;
        flm +=  _in_ptr[44] * 4.0;
        flm +=  _in_ptr[45] * 4.0;
        flm +=  _in_ptr[46] * 4.0;
        flm +=  _in_ptr[47] * 4.0;
        flm +=  _in_ptr[48] * 4.0;
        flm +=  _in_ptr[49] * 4.0;
        flm +=  _in_ptr[50] * 4.0;
        flm +=  _in_ptr[51] * 4.0;
        flm +=  _in_ptr[52] * 4.0;
        flm +=  _in_ptr[53] * 4.0;
        flm +=  _in_ptr[54] * 4.0;
        flm +=  _in_ptr[55] * 4.0;
        flm +=  _in_ptr[56] * 4.0;
        flm +=  _in_ptr[57] * 4.0;
        flm +=  _in_ptr[58] * 4.0;
        flm +=  _in_ptr[59] * 4.0;
        flm +=  _in_ptr[60] * 4.0;
        flm +=  _in_ptr[61] * 4.0;
        flm +=  _in_ptr[62] * 4.0;
        flm +=  _in_ptr[63] * 4.0;
        for (k = 0; k < 64; k++) {
          tmp += force_in_row[k * 256L] * flm;
        }
        j_row = j_col_row;
        out_off = 0 + j_row * 64L;
        _out_ptr =  out_off +  _out_row_ptr;
        _out_ptr[0] = tmp;
      }
      for (k = 0; k < 64; k++) {
        force_in_row[k] = force_in_row[k + 64] + force_in_row[k + 128] + force_in_row[k + 192];
      }
      j_row = i * 256L;
      out_off = 0 + j_row * 64L;
      _out_ptr =  out_off +  _out_row_ptr;
      for (k = 0; k < 64; k++) {
        _out_ptr[k] = force_in_row[k];
      }
    }
}
