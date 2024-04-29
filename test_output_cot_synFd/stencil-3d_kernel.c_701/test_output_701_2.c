#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[27],long sol[27])
{
  long i;
  long j;
  long k;
  long Nx = 27;
  long Ny = 27;
  long Nz = 27;
  long x;
  long y;
  long z;
  long x1;
  long y1;
  long z1;
  long x2;
  long y2;
  long z2;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (i = 1; i < 26; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 1; j < 26; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 1; k < 26; k++) {
        x1 = 0;
        y1 = 0;
        z1 = 0;
        x2 = 0;
        y2 = 0;
        z2 = 0;
        tmp = 0;
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (x = 1; x < 26; x++) {
          if (x != i) {
            x1 += orig[x + 26 * j + 26 * 26 * k];
          }
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (y = 1; y < 26; y++) {
          if (y != j) {
            y1 += orig[i + 26 * y + 26 * 26 * k];
          }
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (z = 1; z < 26; z++) {
          if (z != k) {
            z1 += orig[i + 26 * j + 26 * 26 * z];
          }
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (x = 1; x < 26; x++) {
          if (x != i) {
            x2 += sol[x + 26 * j + 26 * 26 * k];
          }
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (y = 1; y < 26; y++) {
          if (y != j) {
            y2 += sol[i + 26 * y + 26 * 26 * k];
          }
        }
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (z = 1; z < 26; z++) {
          if (z != k) {
            z2 += sol[i + 26 * j + 26 * 26 * z];
          }
        }
        tmp = ((C0 * (x1 + y1 + z1)) + (C1 * (x2 + y2 + z2)));
        sol[i + 26 * j + 26 * 26 * k] = tmp;
      }
    }
  }
}