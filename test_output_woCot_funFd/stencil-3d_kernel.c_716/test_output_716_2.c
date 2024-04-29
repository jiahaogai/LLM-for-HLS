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
  long mem_ij;
  long mem_ij_1;
  long mem_ij_2;
  long mem_ij_3;
  long mem_ij_4;
  long mem_ij_5;
  long mem_ij_6;
  long mem_ij_7;
  long mem_ij_8;
  long mem_ij_9;
  long mem_j;
  long mem_k;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  bound = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj : for(j = 1; j < 32 + 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk_col : for(k_col = 1; k_col < 4 + 1; k_col++) {
      mem_j = 0 + (32 + 1) * (1 + 4) * (k_col - 1);
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi_col : for(i_col = 1; i_col < 32 + 1; i_col++) {
        mem_k = mem_j + (32 + 1) * (i_col - 1);
        mem_ij = mem_k + 1;
        mem_ij_1 = mem_k + (32 + 1);
        mem_ij_2 = mem_ij_1 + (32 + 1);
        mem_ij_3 = mem_ij_2 + (32 + 1);
        mem_ij_4 = mem_ij_3 + (32 + 1);
        mem_ij_5 = mem_ij_4 + (32 + 1);
        mem_ij_6 = mem_ij_5 + (32 + 1);
        mem_ij_7 = mem_ij_6 + (32 + 1);
        mem_ij_8 = mem_ij_7 + (32 + 1);
        mem_ij_9 = mem_ij_8 + (32 + 1);
        sol[mem_ij] = ((2 * orig[mem_ij]) + (orig[mem_ij_1] + orig[mem_ij_2] + orig[mem_ij_3] + orig[mem_ij_4] + orig[mem_ij_5] + orig[mem_ij_6] + orig[mem_ij_7] + orig[mem_ij_8] + orig[mem_ij_9])) / ((long )60);
      }
      
#pragma ACCEL PIPELINE auto{off}
    }
    loopk : for(k = 1; k < 32 + 1 - 4; k++) {
      mem_k = ((32 + 1) * (1 + 4) * (k - 1)) + ((32 + 1) * 1);
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loopi : for(i = 1; i < 32 + 1; i++) {
        mem_ij = mem_k + (i - 1);
        orig[mem_ij] = sol[mem_ij];
      }
    }
  }
}