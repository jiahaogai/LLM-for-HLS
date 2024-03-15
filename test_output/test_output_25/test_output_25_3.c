

#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
        int i_low = i - 1;
        int i_high = i + 1;
        int j_low = j - 1;
        int j_high = j + 1;
        double out = ((double )0);
        double ex0 = ex[i][j];
        double ey0 = ey[i][j];
        double hz0 = hz[i][j];
        double _in_j = ey[i_low][j_high];
        double _in_j_1 = ey[i_low][j];
        double _in_j_2 = ey[i_low][j_low];
        double _in_j_3 = ey[i][j_high];
        double _in_0 = ex[i_high][j_low];
        double _in_1 = ex[i_high][j];
        double _in_2 = ex[i_high][j_high];
        double _in_3 = hz[i_low][j_low];
        double _in_4 = hz[i_low][j];
        double _in_5 = hz[i_low][j_high];
        double _in_6 = hz[i][j_low];
        double _in_7 = hz[i][j_high];
        double _in_8 = hz[i_high][j_low];
        double _in_9 = hz[i_high][j_high];
        out += ((_in_j - ey0) * ((_in_0 - ex0) / (_in_3 - _in_4))) + ((_in_j_1 - ey0) * ((_in_1 - ex0) / (_in_5 - _in_4)));
        out += ((_in_j_2 - ey0) * ((_in_2 - ex0) / (_in_7 - _in_4)));
        out += ((_in_j_3 - ey0) * ((_in_1 - ex0) / (_in_5 - _in_6)));
        ey[i][j] = out;
        hz[i][j] = ex0 - 0.5 * (ex[i][j] - ex[i][j]) + 0.5 * (ey[i][j] - ey0) + 0.5 * (hz[i][j] - hz0) + 0.5 * (_in_8 - hz0);
      }
    }
  }
}
