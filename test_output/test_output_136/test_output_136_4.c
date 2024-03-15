
 #pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
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
        z_sum = hz[i][j] + hz[i][j + 1] + hz[i + 1][j] + hz[i + 1][j + 1];
        hz[i][j] = z_sum;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L1}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
    for (i = 0; i < 200 - 1; i++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L8}
      for (j = 0; j < 240 - 1; j++) {
        e_x = ex[i][j] - ex[i][j + 1];
        e_y = ey[i][j] - ey[i + 1][j];
        e_z = hz[i][j] - hz[i + 1][j + 1];
        r_x = sqrt((double )((e_x * e_x) + (e_y * e_y) + (e_z * e_z)));
        tmp = 0.05 * r_x;
        p_x = e_x - (tmp * e_x);
        p_y = e_y - (tmp * e_y);
        p_z = e_z - (tmp * e_z);
        ex[i][j] = p_x;
        ey[i][j] = p_y;
        hz[i][j] = p_z;
        q_x = p_y * e_z - p_z * e_y;
        q_y = p_z * e_x - p_x * e_z;
        q_z = p_x * e_y - p_y * e_x;
        div = q_x + q_y + q_z;
        ex[i][j + 1] = ex[i][j] + q_x;
        ey[i + 1][j] = ey[i][j] + q_y;
        hz[i][j + 1] = hz[i][j] + q_z;
        _fict_[i * j] = div;
      }
    }
  }
}
