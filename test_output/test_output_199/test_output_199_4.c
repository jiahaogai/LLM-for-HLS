

#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{64}
    for (i = 1; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L5}
      for (j = 0; j < 240; j++) {
        ey[i][j] = ey[i][j] - 0.5 * (hz[i][j] - hz[i - 1][j]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (i = 0; i < 200; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L6}
      for (j = 1; j < 240; j++) {
        ex[i][j] = ex[i][j] - 0.5 * (hz[i][j] - hz[i][j - 1]);
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L4}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L4}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L7}
      for (j = 0; j < 240 - 1; j++) {
        int i_col = -1;
        int j_col = -1;
        double dxy_x = 0.0;
        double dxy_y = 0.0;
        double ex_x = 0.0;
        double ex_y = 0.0;
        double ey_x = 0.0;
        double ey_y = 0.0;
        double hz_x = 0.0;
        double hz_y = 0.0;
        double _in_x = ((double )i) + 1.0;
        double _in_y = ((double )j) + 1.0;
        dxy_x = ((double )i) * (ey[i][j + 1] - ey[i][j]) - (((double )j) * (ex[i + 1][j] - ex[i][j]));
        dxy_y = ((ey[i + 1][j] - ey[i][j]) - ((double )(j + 1) * (ex[i + 1][j] - ex[i][j]))) / ((double )(i + 1));
        ex_x = ex[i + 1][j + 1] - ex[i][j + 1];
        ex_y = ex[i + 1][j] - ex[i][j];
        ey_x = ey[i + 1][j + 1] - ey[i][j + 1];
        ey_y = ey[i + 1][j] - ey[i][j];
        hz_x = hz[i + 1][j + 1] - hz[i][j + 1];
        hz_y = hz[i + 1][j] - hz[i][j];
        int _in_blk_idx = 0;
        int _in_vec_idx = 0;
        i_col = 2;
        for (j_col = 2; j_col < 32; j_col++) {
          if (j_col >= 2) {
            i_col *= 4;
          }
          int _tmp_222 = 0;
          int _tmp_223 = 0;
          _tmp_222 = 4 * i_col + 2;
          _tmp_223 = 4 * j_col + 2;
          double _tmp_224 = ((double )_tmp_222) + 1.0;
          double _tmp_225 = ((double )_tmp_223) + 1.0;
          double _tmp_226 = _tmp_224 * _in_x;
          double _tmp_227 = _tmp_225 * _in_y;
          double _tmp_228 = _in_x + 1.0;
          double _tmp_229 = _in_y + 1.0;
          double _tmp_230 = _tmp_228 * _tmp_227;
          double _tmp_231 = dxy_x * (_tmp_226 * _tmp_230 - _tmp_227 * _tmp_226);
          double _tmp_232 = ey_x * (hz[i_col + 1][j_col + 1] - hz[i_col][j_col + 1]) - ey_y * (hz[i_col + 1][j_col] - hz[i_col][j_col]);
          double _tmp_233 = dxy_y * (_tmp_226 * _tmp_232 - _tmp_227 * _tmp_233) + ey_x * (_tmp_227 * _tmp_233 - _tmp_232 * _tmp_227);
          double _tmp_234 = ex_x * (hz[i_col + 1][j_col + 1] - hz[i_col + 1][j_col]) - ex_y * (hz[i_col][j_col + 1] - hz[i_col][j_col]);
          double _tmp_235 = ex_x * (_tmp_227 * _tmp_234 - _tmp_234 * _tmp_227) + ex_y * (_tmp_234 * _tmp_226 - _tmp_226 * _tmp_234);
          double _tmp_236 = hz[i_col][j_col] + 1.0 / (2.0 * (((double )((int )25)) * 1.0)) * (__PARA__L9 * (dxy_x * _tmp_231 + dxy_y * _tmp_233 + ex_x * _tmp_235 + ey_y * _tmp_234 - (ey_x * _tmp_233 + ex_y * _tmp_231)) - _fict_[t]);
          hz[i_col][j_col] = _tmp_236;
        }
      }
    }
  }
}
