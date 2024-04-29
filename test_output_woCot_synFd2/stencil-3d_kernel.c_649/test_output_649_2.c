Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long idxm1;
  long idxp1;
  long idxm1m1;
  long idxm1p1;
  long idxp1p1;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_j:
/* Standardize from: for(j = 1;j < 32 + 1 - 1;j++) {...} */
  for (j = 1 + 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_k:
/* Standardize from: for(k = 1;k < 32 + 1 - 1;k++) {...} */
    for (k = 1 + 1; k < 32 + 1 - 1; k++) {
      idx = 32 * (1 + 32) * (k + 32 * j) + 1;
      idxm1 = idx - 1;
      idxp1 = idx + 1;
      idxm1m1 = idx - 33;
      idxm1p1 = idx - 32;
      idxp1p1 = idx + 32;
      tmp = orig[idxm1m1] + orig[idxm1p1] + orig[idxp1p1] + orig[idxm1] + 4 * orig[idxp1] + orig[idxm1m1];
      sol[idx] = tmp;
/* Standardize from: for(i = 1;i < 32 + 1 - 1;i++) {...} */
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_i:
      for (i = 1 + 1; i < 32 + 1 - 1; i++) {
        tmp = orig[idxm1m1] + orig[idxm1p1] + orig[idxp1p1] + orig[idxm1] + 4 * orig[idxp1] + orig[idxm1m1];
        sol[idx] = tmp;
        idx++;
        idxm1--;
        idxp1++;
        idxm1m1--;
        idxm1p1++;
        idxp1p1++;
      }
    }
    k = 0;
    while (k < 32) {
      j = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_j:
      while (j < 32) {
        i = 0;
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        loop_i:
        while (i < 32) {
          orig[32 * (1 + 32) * (k + 32) + 32 * (1 + 1) * (j + 1) + 1 + 1 + i] = sol[32 * (1 + 32) * (k + 32) + 32 * (1 + 1) * (j + 1) + 1 + 1 + i];
          i++;
        }
        j++;
      }
      k++;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil3d’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:61:7: error: duplicate label ‘loop_j’
   61 |       loop_j: