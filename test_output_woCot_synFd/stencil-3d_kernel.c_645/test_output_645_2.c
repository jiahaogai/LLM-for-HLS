#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  sp1(C0,orig,sol);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  sp2(C0,orig,sol);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  sp3(C1,orig,sol);
}
extern void sp1(long ,long [] ,long [] );
extern void sp2(long ,long [] ,long [] );
extern void sp3(long ,long [] ,long [] );
#pragma ACCEL kernel

void sp1(long C0,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  long x;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 0; j < 40; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 0; k < 40; k++) {
      idx = (j * 40) + k;
      x = orig[idx];
      loopki:
      for (i = 0; i < 40; i++) {
        k_col = (k * 40) + i;
        i_col = (j * 40) + i;
        idx_col = k_col * 256 + i_col;
        t = C0 * (x - orig[k_col]) - orig[i_col] + sol[idx_col];
        sol[idx_col] = t;
      }
    }
  }
}
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{1}
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{8}
#pragma ACCEL PARALLEL FACTOR=auto{1}
#pragma ACCEL kernel

void sp2(long C0,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  long x;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 0; j < 40; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 0; k < 40; k++) {
      idx = (j * 40) + k;
      x = orig[idx];
      loopki:
      for (i = 0; i < 40; i++) {
        k_col = (k * 40) + i;
        i_col = (j * 40) + i;
        idx_col = k_col * 40 + i_col;
        t = C0 * (x - orig[k_col]) - orig[i_col] + sol[idx_col];
        sol[idx_col] = t;
      }
    }
  }
}
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{8}
#pragma ACCEL PARALLEL FACTOR=auto{1}
#pragma ACCEL kernel

void sp3(long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long i_col;
  long idx;
  long idx_col;
  long t;
  long x;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 0; j < 40; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 0; k < 40; k++) {
      idx = (j * 40) + k;
      x = orig[idx];
      loopki:
      for (i = 0; i < 40; i++) {
        k_col = (k * 40) + i;
        i_col = (j * 40) + i;
        idx_col = k_col * 40 + i_col;
        t = C1 * (x - orig[k_col]) - orig[i_col] + sol[idx_col];
        sol[idx_col] = t;
      }
    }
  }
}