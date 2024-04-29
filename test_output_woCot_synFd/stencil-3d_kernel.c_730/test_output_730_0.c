#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long ko;
  long kj;
  long ki;
  long idx;
  long idxm1;
  long idxp1;
  long idxm1p1;
  long idxp1p1;
  long C02;
  long C12;
  C02 = C0 + 2;
  C12 = C1 + 2;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loop_i:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loop_j:
    for (j = 0; j < 32; j++) {
      loop_k:
      for (k = 0; k < 32; k++) {
        ko = k;
        kj = (j * 32) + ko;
        ki = (i * 32) + ko;
        idx = (ki * 32) + kj;
        idxm1 = idx - 1;
        idxp1 = idx + 1;
        idxm1p1 = idxm1 + 1;
        idxp1p1 = idxp1 + 1;
        sol[idx] = ((C0 * orig[idx]) + (C1 * (orig[idxm1] + orig[idxp1] + orig[idxm1p1] + orig[idxp1p1])));
      }
    }
  }
}