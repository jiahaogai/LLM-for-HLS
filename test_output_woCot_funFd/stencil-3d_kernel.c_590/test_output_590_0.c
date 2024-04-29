#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long x;
  long y;
  long z;
  long xm;
  long xm1;
  long xp;
  long xp1;
  long ym;
  long ym1;
  long yp;
  long yp1;
  long zm;
  long zm1;
  long zp;
  long zp1;
  long A;
  long B;
  long C;
  long D;
  long E;
  long F;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_x:
/* Standardize from: for(x = 1;x < 32 + 1;x++) {...} */
  for (x = 1; x <= 32 + 1 - 1; x++) {
    xm = 0;
    xm1 = x - 1;
    xp1 = x + 1;
    if (32 + 1 - xp1 > 0) {
      xp = xp1 - (32 + 1 - xp1);
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_y:
/* Standardize from: for(y = 1;y < 32 + 1;y++) {...} */
    for (y = 1; y <= 32 + 1 - 1; y++) {
      ym = 0;
      ym1 = y - 1;
      yp1 = y + 1;
      if (32 + 1 - yp1 > 0) {
        yp = yp1 - (32 + 1 - yp1);
      }
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_z:
/* Standardize from: for(z = 1;z < 32 + 1;z++) {...} */
      for (z = 1; z <= 32 + 1 - 1; z++) {
        zm = 0;
        zm1 = z - 1;
        zp1 = z + 1;
        if (32 + 1 - zp1 > 0) {
          zp = zp1 - (32 + 1 - zp1);
        }
        idx = xm1 + ym1 + zm1;
        A = orig[idx];
        B = orig[xm1 + ym1 + z];
        C = orig[xm1 + y + zm1];
        D = orig[xm1 + yp1 + zm1];
        E = orig[x + ym1 + zm1];
        F = orig[xp1 + ym1 + zm1];
        sol[idx] = A + B + C + D + E + F - C0 * (A + D) - C1 * (B + F);
      }
    }
  }
}