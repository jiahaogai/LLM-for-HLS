#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long mem_ai;
  long mem_aj;
  long mem_ak;
  long idx;
  long ajk;
  long ai;
  long aj;
  long ak;
  long fila;
  long columna;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loop_i:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1 + 32; i > 1 + 32 - 1; i--) {
    ia:
    for (ai = 0; ai < 32 + 0; ai++) {
      mem_ai = ai * 32 + i;
      idx = mem_ai;
      ak = orig[idx];
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_j:
/* Standardize from: for(j = 1; j < 32 + 1; j++) {...} */
      for (j = 1 + 32; j > 1 + 32 - 1; j--) {
        jc:
        for (aj = 0; aj < 32 + 0; aj++) {
          mem_aj = aj * 32 + j;
          ajk = mem_aj * 32 + ai;
          orig[ajk] = ak;
        }
        ak = orig[idx - 1] + orig[idx + 1] + orig[idx - 32] + orig[idx + 32] + C0;
      }
    }
    loop_k:
/* Standardize from: for(k = 1; k < 32 + 1; k++) {...} */
    for (k = 1 + 32; k > 1 + 32 - 1; k--) {
      kc:
      for (ak = 0; ak < 32 + 0; ak++) {
        mem_ak = ak * 32 + k;
        idx = mem_ak;
        sol[idx] = ak * C1 + ak * orig[idx] + orig[idx];
      }
    }
  }
}