#pragma ACCEL kernel

void stencil3d(long C0,long C1,long C2,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long idx;
  long _in;
  long _out;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{30}
  loop_x:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_y:
    for (j = 0; j < 32; j++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_z:
      for (k = 0; k < 32; k++) {
        _out = ((i + 2) % 32) * 32 * 32 + ((j + 2) % 32) * 32 + ((k + 2) % 32);
        _in = i * 32 * 32 + j * 32 + k;
        sol[_out] = ((long )0);
        
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
        loop_k:
        for (idx = 0; idx < 30; idx++) {
          sol[_out] += orig[_in] * filter[idx];
          _in++;
        }
      }
    }
  }
}