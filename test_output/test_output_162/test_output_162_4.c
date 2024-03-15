
#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{5}
    for (j = 0; j < 240; j++) {
      ey[0][j] = _fict_[t];
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L2}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
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
        int i_low = 1 + 0 * (1L << 0);
        int i_high = 1 + 1 * (1L << 0);
        int j_low = 1 + 0 * (1L << 5);
        int j_high = 1 + 1 * (1L << 5);
        double DX = 1.0;
        double DY = 1.0;
        double DZ = 1.0;
        double C1 = -1.0 / (DX * DX);
        double C2 = -1.0 / (2.0 * DY * DY);
        double C3 = -1.0 / (DZ * DZ);
        double C4 = 2.0 * (C2 + C3);
        double C5 = C1 + C4;
        double EXT_A = ex[i][j];
        double EXT_B = ey[i][j];
        double EXT_C = hz[i][j];
        double dJdX = 2.0;
        double dJdY = 2.0 * ( (404) - 1);
        double dJdZ = 2.0 * ( (240) - 1);
        double partial[9];
        partial[0] = C5 * (EXT_A - ex[i_low][j]);
        partial[1] = C4 * (EXT_A - ex[i_high][j]);
        partial[2] = C4 * (EXT_A - ex[i_low][j_low]) - C5 * (EXT_A - ex[i_high][j_low]) + C2 * (EXT_B - ey[i][j_low]);
        partial[3] = C4 * (EXT_A - ex[i_high][j_low]) - C5 * (EXT_A - ex[i_low][j_high]) - C2 * (EXT_B - ey[i][j_high]);
        partial[4] = C4 * (EXT_A - ex[i_low][j_high]) - C5 * (EXT_A - ex[i_high][j_high]) + C2 * (EXT_B - ey[i][j_low] - dJdY * ey[i][j_high]);
        partial[5] = C1 * (EXT_C - hz[i_low][j]);
        partial[6] = C4 * (EXT_A - ex[i_low][j_low]) - C5 * (EXT_A - ex[i_high][j_high]) + C3 * (EXT_C - hz[i_low][j_low]) - C5 * (EXT_C - hz[i_high][j_high]) + C2 * (EXT_B - ey[i][j_low] - dJdY * ey[i][j_high] - dJdX * hz[i][j_low] + dJdX * hz[i][j_high]);
        partial[7] = C4 * (EXT_A - ex[i_high][j_low]) - C5 * (EXT_A - ex[i_low][j_high]) - C3 * (EXT_C - hz[i_high][j_low]) - C5 * (EXT_C - hz[i_low][j_high]) + C2 * (EXT_B - ey[i][j_low] - dJdY * ey[i][j_high] - dJdX * hz[i][j_low] - dJdX * hz[i][j_high]);
        partial[8] = C5 * (EXT_B - ey[i_low][j]) - C4 * (EXT_B - ey[i_high][j]) + C3 * (EXT_C - hz[i_low][j]) - C5 * (EXT_C - hz[i_high][j]) + 2.0 * (C4 * (EXT_C - hz[i][j]) + C1 * (EXT_A - ex[i][j]) - C2 * (EXT_B - ey[i][j]));
        double A = partial[0] + partial[1] + partial[4];
        double B = partial[1] + partial[2] + partial[5];
        double C = partial[4] + partial[5] + partial[8];
        double D = partial[2] + partial[3] + partial[6];
        double E = partial[3] + partial[7] + partial[8];
        double F = partial[6] + partial[7];
        double G = ex[i][j] - (A * ey[i][j] + B * hz[i][j]);
        double H = ey[i][j] - (C * ey[i][j] + D * hz[i][j]);
        double I = hz[i][j] - (E * ey[i][j] + F * hz[i][j]);
        ex[i][j] = G;
        ey[i][j] = H;
        hz[i][j] = I;
      }
    }
  }
}
