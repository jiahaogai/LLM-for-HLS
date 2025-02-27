#pragma ACCEL PIPELINE auto{off}
Error: 
Please check the code and try again.
 #pragma ACCEL TILE FACTOR=auto{2}
Error: 
Please check the code and try again.

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long sum0;
  long sum1;
  long mul0;
  long mul1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  for (long i = 1; i < 33; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (long j = 1; j < 33; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (long ko = 0; ko <= 31; ko++) {
        long _in_ko = 1L + 1L * ko;
        sum0 = orig[_in_ko + (0) + (34) * (j + (34) * i)];
        sum1 = orig[_in_ko + (0) + (34) * (j + (34) * (i + (1)))] + orig[_in_ko + (0) + (34) * (j + (34) * (i - (1)))] + orig[_in_ko + (0) + (34) * (j + (1) + (34) * i)] + orig[_in_ko + (0) + (34) * (j - (1) + (34) * i)] + orig[_in_ko + (0) + (1) + (34) * (j + (34) * i)] + orig[_in_ko + (0) - (1) + (34) * (j + (34) * i)];
        mul0 = sum0 * C0;
        mul1 = sum1 * C1;
        sol[_in_ko + (0) + (34) * (j + (34) * i)] = mul0 + mul1;
      }
    }
  }
}