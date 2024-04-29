Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long t;
  long pt;
  long index;
  long C2;
  long C3;
  C2 = 16;
  C3 = 64;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 2;j < 39302;j++) {...} */
  for (j = 0; j <= 39301; j++) {
    long jj;
    jj = ((2) + (j)) - 1;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 2;k < 32766;k++) {...} */
    for (k = 0; k <= 32765; k++) {
      long kk;
      long i_col;
      long j_col;
      long k_col;
      long sum;
      long kk_col;
      kk = ((2) + (k)) - 1;
      i_col = ((0) + (-1)) + 39303;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi:
      for (i = 0; i < 39304; i++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{8}
        loopk_col:
        for (k_col = 0; k_col < 64; k_col++) {
          j_col = 0;
          
#pragma ACCEL PIPELINE auto{off}
          loopj_col:
          for (; j_col < 16; j_col++) {
            pt = ((kk_col * 16) + j_col) - 1;
            t = orig[i_col + pt];
            sum = t;
            
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
            loopk:
            for (; k_col < 64 + 1; k_col++) {
              if ((((k - 2) + k_col) > -1) && (((k - 2) + k_col) < 32766)) {
                index = ((kk * 64) + k_col) - 1;
                sum += orig[index] * C1;
              }
            }
            sol[i + pt] = sum;
          }
        }
        i_col = i_col + 1;
        kk_col = kk_col + 1;
      }
    }
    k = ((0) + (64) + (-1)) + 32765;
  }
  j = ((0) + (16) + (-1)) + 39301;
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil3d’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:61:13: error: duplicate label ‘loopk’
   61 |             loopk:
      |             ^~~~~
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:28:5: note: previous definition of ‘loopk’ was here
   28 |     loopk:
      |     ^~~~~

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long