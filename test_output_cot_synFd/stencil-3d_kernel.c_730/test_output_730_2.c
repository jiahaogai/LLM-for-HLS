#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{32}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long ko;
  long jj;
  long ii;
  long kk;
  long idx;
  long idxm1;
  long idxp1;
  long idxm1m1;
  long idxm1p1;
  long idxp1p1;
  long idxp1m1;
  long C02;
  long C12;
  long orig_idx;
  long sol_idx;
  C02 = C0 + 2;
  C12 = C1 + 2;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (k = 0; k < 32; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (i = 0; i < 32; i++) {
        idx = i + 32l * (j + 32l * k);
        idxm1 = idx - 1;
        idxp1 = idx + 1;
        idxm1m1 = idx - 32l - 1;
        idxm1p1 = idx - 32l + 1;
        idxp1p1 = idx + 32l + 1;
        idxp1m1 = idx + 32l - 1;
        C02 = C0;
        C12 = C1;
        orig_idx = 39304l * k + 32l * j + i;
        sol_idx = 32768l * k + 32l * j + i;
        sol[sol_idx] = ((C02 * orig[orig_idx]) + (C12 * (orig[idxp1] + orig[idxm1] + orig[idxp1p1] + orig[idxp1m1] + orig[idxm1m1] + orig[idxm1p1])));
      }
    }
  }
//#pragma endscop
}