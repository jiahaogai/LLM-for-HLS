#pragma ACCEL kernel

void kernel_fdtd_2d(int tmax,int nx,int ny,double ex[200][240],double ey[200][240],double hz[200][240],double _fict_[100])
{
  int t;
  int x;
  int y;
  double Jx;
  double Jy;
  double Jz;
  double _fict_;
  double ex_[200][240];
  double ey_[200][240];
  double hz_[200][240];
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (t = 0; t < 100; t++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (x = 1; x < 200 - 1; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
      for (y = 1; y < 240 - 1; y++) {
        Jx = -1.0 * (ey[x][y + 1] - ey[x][y - 1]) / (2 * (double )240);
        Jy = -1.0 * (ex[x + 1][y] - ex[x - 1][y]) / (2 * (double )200);
        Jz = -1.0 * (ex[x][y] - ey[x][y]) / (2 * (double )240);
        ex[x][y] = ex_[x][y] + 0.5 * Jx;
        ey[x][y] = ey_[x][y] + 0.5 * Jy;
        hz[x][y] = hz_[x][y] + 0.5 * Jz;
      }
    }
    
#pragma ACCEL PIPELINE auto{__PIPE__L3}
    
#pragma ACCEL TILE FACTOR=auto{__TILE__L3}
    
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
    for (x = 1; x < 200 - 1; x++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L4}
      for (y = 1; y < 240 - 1; y++) {
        Jx = -1.0 * (ey[x][y + 1] - ey[x][y - 1]) / (2 * (double )240);
        Jy = -1.0 * (ex[x + 1][y] - ex[x - 1][y]) / (2 * (double )200);
        Jz = -1.0 * (ex[x][y] - ey[x][y]) / (2 * (double )240);
        ex_[x][y] = ex[x][y] + 0.5 * (Jx - Jy);
        ey_[x][y] = ey[x][y] + 0.5 * (Jy - Jz);
        hz_[x][y] = hz[x][y] + 0.5 * (Jz - ex[x][y] + ey[x][y]);
      }
    }
  }
//#pragma endscop
}