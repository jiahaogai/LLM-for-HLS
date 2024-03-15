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
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
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
        double _in_1 = 0.0;
        double _in_2 = 0.0;
        double _in_3 = 0.0;
        double _in_4 = 0.0;
        double _in_5 = 0.0;
        double _in_6 = 0.0;
        double _in_7 = 0.0;
        double _in_8 = 0.0;
        i_col = 1 + i;
        j_col = 1 + j;
        dxy_x = (((double )ex[i_col][j]) - ((double )ex[i][j])) / (((double )(i + 1)) - ((double )i));
        dxy_y = (((double )ey[i][j_col]) - ((double )ey[i][j])) / (((double )(j_col + 1)) - ((double )(j)));
        ex_x = dxy_x - ey[i][j] * dxy_y;
        ex_y = ey[i_col][j] * dxy_x - dxy_y;
        ey_x = dxy_x + ey[i][j] * dxy_y;
        ey_y = ((double )-1.0) * dxy_x - ex[i][j] * dxy_y;
        hz_x = dxy_x - 0.5 * (hz[i_col][j] - hz[i][j]);
        hz_y = dxy_y - 0.5 * (hz[i][j_col] - hz[i][j]);
        _in_1 = ex[i][j] + ex_x;
        _in_2 = ey[i][j] + ex_y;
        _in_3 = hz[i][j] + hz_x;
        _in_4 = _in_2 + ey_x;
        _in_5 = ey[i][j_col] + ey_y;
        _in_6 = hz[i][j_col] + hz_y;
        _in_7 = _in_1 * _in_4;
        _in_8 = _in_3 * _in_5;
        ex[i][j] = _in_7;
        ey[i][j] = _in_8;
        hz[i][j] = _in_6;
      }
    }
  }
}
