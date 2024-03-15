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
        double dxy = 0.0;
        double ex_x = 0.0;
        double ey_y = 0.0;
        double hz_x = 0.0;
        double hz_y = 0.0;
        double _in_0 = ex[i][j];
        data_t ex_0 = _in_0;
        data_t ey_x = diff_coef->ey[i][j] * ex_0;
        data_t hz_x_x = diff_coef->hz[i][j] * ex_x;
        data_t ey_y_x = diff_coef->ey[i][j] * ey_x;
        data_t hz_x_x_x = diff_coef->hz[i][j] * hz_x_x;
        data_t tmp = ey[i][j + 1];
        data_t hz_y_x = diff_coef->hz[i][j] * ey_y_x;
        data_t tmp_x = ey[i + 1][j];
        data_t del_x = tmp_x - tmp;
        data_t _in_1 = del_x;
        data_t ey_y_x_x = _in_1 * ey_y_x;
        data_t _in_2 = hz[i][j];
        data_t hz_z_x = _in_2 * hz_x_x;
        data_t _in_3 = tmp;
        data_t hz_z_x_x = _in_3 * hz_x_x_x;
        data_t dxy_x = ey_y_x_x + hz_z_x_x;
        data_t _in_4 = hz[i + 1][j];
        data_t hz_z_y = _in_4 * hz_y_x;
        data_t _in_5 = tmp;
        data_t hz_z_y_x = _in_5 * hz_y_x_x;
        data_t dxy_y = hz_z_y + hz_z_y_x;
        data_t n = -1.0;
        data_t dt = 1.0;
        data_t dx = 1.0;
        data_t dy = 1.0;
        data_t dzt = dt * dx * dy;
        data_t dxy_dt = dxy * dt;
        data_t dxy_dx = dxy_x * dx;
        data_t dxy_dy = dxy_y * dy;
        data_t six_dx2 = 6.0 * (dx * dx);
        data_t six_dy2 = 6.0 * (dy * dy);
        data_t five_dz2 = 5.0 * (dzt * dzt);
        data_t five_dx2_dt2 = 2.0 * (five_dx2 * (dt * dt));
        data_t five_dy2_dt2 = 2.0 * (five_dy2 * (dt * dt));
        data_t four_dz2_dt2 = 2.0 * (four_dz2 * (dt * dt));
        data_t five_dx_dt = 5.0 * (dx * (dt));
        data_t five_dy_dt = 5.0 * (dy * (dt));
        data_t four_dz_dt = 4.0 * (dzt * (dt));
        data_t four_dx2_dy2 = four_dx2 * four_dy2;
        data_t four_dx2_dz2 = four_dx2 * four_dz2;
        data_t four_dy2_dz2 = four_dy2 * four_dz2;
        data_t four_dx_dt2 = 4.0 * (dx * (dt * dt));
        data_t four_dy_dt2 = 4.0 * (dy * (dt * dt));
        data_t four_dz_dt2 = 4.0 * (dzt * (dt * dt));
        data_t p = ((((six_dx2 * ey_y + six_dy2 * ex_x) + hz_x_x) + hz_y_y) - (dxy_dt + (n * dzt)));
        data_t q = ((((six_dx2 * ey_x + six_dy2 * ex_y) + hz_x_y) + hz_y_x) - (dxy_dx + (n * dzt)));
        data_t r = (((four_dx2_dt2 * ey_y + four_dy2_dt2 * ex_x) + four_dz2_dt2 * ex_ex_x) + (((four_dx2_dy2 * ey_y + four_dy2_dx2 * ex_x) + four_dz2_dx2 * ex_ey_x) + hz_x_x) - (dxy_dx * dxy_dt + (n * (four_dz2_dx2 * ex_x + four_dx2_dz2 * ey_x + two_dz_dt * (ex_x * ex_x + ey_x * ey_