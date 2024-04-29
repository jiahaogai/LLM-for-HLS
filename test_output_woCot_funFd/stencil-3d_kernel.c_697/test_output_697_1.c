#pragma ACCEL kernel

void stencil3d(long C0,long C1,double orig[27][27][27],double sol[27][27][27])
{
  long r;
  long q;
  long p;
  long s;
  long t;
  long u;
  double B[3];
  double A[3][3][3];
  r = 1 + 2;
  q = 1 + 2;
  p = 1 + 2;
  s = 0;
  t = 0;
  u = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (v = 0; v < 3; v++) {
    B[v] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (w = 0; w < 3; w++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (x = 0; x < 3; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (y = 0; y < 3; y++) {
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          for (z = 0; z < 3; z++) {
            A[v][w][x][y][z] = orig[r + v - 1][q + w - 1][p + x - 1] * coef[0][z] * coef[1][y] * coef[2][x];
          }
        }
      }
    }
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (v = 0; v < 3; v++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (w = 0; w < 3; w++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (x = 0; x < 3; x++) {
          
#pragma ACCEL PARALLEL reduction=B[v] FACTOR=auto{1}
          for (y = 0; y < 3; y++) {
            
#pragma ACCEL PARALLEL FACTOR=auto{1}
            for (z = 0; z < 3; z++) {
              B[v] += A[v][w][x][y][z];
            }
          }
        }
      }
    }
    sol[r - 1][q - 1][p - 1] = B[0] + B[1] + B[2];
  }
}