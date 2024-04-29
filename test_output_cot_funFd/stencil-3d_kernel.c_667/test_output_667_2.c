Code: ### Generated Code:
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
  long t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  bound = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  i_col = 1 - bound;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  j_col = 1 - bound;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  k_col = 1 - bound;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  i = 1 + bound;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  while (i < 32 + bound) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    j = 1 + bound;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{4}
    while (j < 32 + bound) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      k = 1 + bound;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      while (k < 32 + bound) {
        t = ((((k_col + 1) * 32) + (j_col + 1)) * 32) + i_col + 1;
        sol[((((k + 1) - 1) * 32) + (j + 1)) - ((1 + -1) * 32)] = (((((C0 * (orig[t - 32] + orig[t - 1] + orig[t + 1] + orig[t + 32]) / 4) + (C1 * (orig[t - 31] + orig[t - 1 + 1] + orig[t + 1 + 1] + orig[t + 31]))) / 2) + orig[t]) / 2);
        k++;
      }
      k_col++;
    }
    j_col++;
    j = 1 + bound;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    while (j < 32 + bound) {
      i_col = 1 - bound;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      while (i_col < 32 + bound) {
        t = ((((k_col + 1) * 32) + (j_col + 1)) * 32) + i_col + 1;
        sol[((((k + 1) - 1) * 32) + (j + 1)) - ((1 + -1) * 32)] = (((((C0 * (orig[t - 32] + orig[t - 1] + orig[t + 1] + orig[t + 32]) / 4) + (C1 * (orig[t - 31] + orig[t - 1 + 1] + orig[t +