Code: 
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  long s;
  long k_row;
  long j_row;
  long i_row;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (k = 0; k < 32; k++) {
        i_row = i * 32 + flatten(0, 31);
        j_row = j * 32 + flatten(0, 31);
        k_row = k * 32 + flatten(0, 31);
        buf = 0;
        i_col = i_row + 1;
        if (i_col == 39304) {
          i_col = 0;
        }
        
#pragma ACCEL PIPELINE auto{off}
        j_col = j_row + 1;
        if (j_col == 39304) {
          j_col = 0;
        }
        
#pragma ACCEL PIPELINE auto{off}
        k_col = k_row + 1;
        if (k_col == 39304) {
          k_col = 0;
        }
        s = 0;
        buf += C0 * (long )orig[i_col * 39304 + j_col * 32 + k_col];
        s += 1;
        buf += C1 * (long )orig[i_col * 39304 + j_col * 32 + k_col];
        sol[i * 32 + j * 32 + k] = buf / (long )s;
      }
    }
  }
//#pragma endscop
}