#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
<<<<<<< HEAD
  long k_col;
  long j_col;
  long i_col;
  long buf[256];
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopk:
/* Standardize from: for(k = 1; k < 40; k++) {...} */
  for (k = 1 + 0; k < 40 + 0; k++) {
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
    loopj:
/* Standardize from: for(j = 1; j < 40; j++) {...} */
    for (j = 1 + 0; j < 40 + 0; j++) {
=======
    loop_y:
/* Standardize from: for(y = 1;y < 32 + 1;y++) {...} */
    for (y = 1; y <= 32 + 1 - 1; y++) {
      ym = 0;
      ym1 = y - 1;
      yp1 = y + 1;
      if (32 + 1 - yp1 > 0) {
        yp = yp1 - (32 + 1 - yp1);
      }
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
<<<<<<< HEAD
      loopi:
/* Standardize from: for(i = 1; i < 40; i++) {...} */
      for (i = 1 + 0; i < 40 + 0; i++) {
        i_col = i - 1 + ((j - 1) * 40) + ((k - 1) * 40 * 40);
        j_col = j - 1 + ((k - 1) * 40);
        k_col = k - 1;
        tmp = 0;
        loopbuf:
        for (long b = 0; b < 256; ++b) {
          tmp += orig[i_col * 256 + b] * buf[b];
        }
        sol[i_col] = tmp;
=======
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
>>>>>>> aacacb78d0cb9c57b2f479851f61349c1954fe7a
      }
    }
  }
}