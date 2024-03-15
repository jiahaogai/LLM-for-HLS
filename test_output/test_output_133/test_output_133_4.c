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
        double  delta_x = (double )(ex[i][j + 1] - ex[i][j]);
        double  delta_y = (double )(ey[i + 1][j] - ey[i][j]);
        double  delta_z = (double )(hz[i + 1][j] - hz[i][j]);
        double  si_x = delta_x / (4.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  si_y = delta_y / (4.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  si_z = delta_z / (4.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  co_x = - 1.0 * delta_x / (2.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  co_y = - 1.0 * delta_y / (2.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  co_z = - 1.0 * delta_z / (2.0 * (1.0 + delta_x * delta_x + delta_y * delta_y));
        double  r_x = si_x - ex[i][j] ;
        double  r_y = si_y - ey[i][j] ;
        double  r_z = si_z - hz[i][j] ;
        double  t_x = - 1.0 * co_x - ex[i][j] ;
        double  t_y = - 1.0 * co_y - ey[i][j] ;
        double  t_z = - 1.0 * co_z - hz[i][j] ;
        double  w_x = co_x - ex[i][j] ;
        double  w_y = co_y - ey[i][j] ;
        double  w_z = co_z - hz[i][j] ;
        double  b_x = ((double )7.0) * (r_x - t_x) ;
        double  b_y = ((double )7.0) * (r_y - t_y) ;
        double  b_z = ((double )7.0) * (r_z - t_z) ;
        double  c_x = w_x - ((double )2.0) * r_x ;
        double  c_y = w_y - ((double )2.0) * r_y ;
        double  c_z = w_z - ((double )2.0) * r_z ;
        double  e_x = ((double )2.0) * r_x ;
        double  e_y = ((double )2.0) * r_y ;
        double  e_z = ((double )2.0) * r_z ;
        double  d_x = ((double )2.0) * (co_x - ex[i + 1][j]) ;
        double  d_y = ((double )2.0) * (co_y - ey[i + 1][j]) ;
        double  d_z = ((double )2.0) * (co_z - hz[i + 1][j]) ;
        ex[i][j] = e_x + ((double )1.0 / (12.0)) * (b_x + ((double )4.0) * (c_x + d_x));
        ey[i][j] = e_y + ((double )1.0 / (12.0)) * (b_y + ((double )4.0) * (c_y + d_y));
        hz[i][j] = e_z + ((double )1.0 / (12.0)) * (b_z + ((double )4.0) * (c_z + d_z));
      }
    }
  }
}
