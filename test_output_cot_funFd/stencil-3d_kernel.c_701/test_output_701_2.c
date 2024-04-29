#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[27],long sol[27])
{
  long i;
  long j;
  long k;
  long idx;
  long delta;
  long tmp[8];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  for (k = 0; k < 4; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 4; i++) {
        idx = ((k * 4) + j) * 4 + i;
        delta = ((C0 + 1) * (C1 + 1) * (C1 + 1)) * 4;
        tmp[0] = orig[idx];
        tmp[1] = orig[idx + 1];
        tmp[2] = orig[idx + 1 + C1];
        tmp[3] = orig[idx + C1];
        tmp[4] = orig[idx - 1 + C1];
        tmp[5] = orig[idx - 1];
        tmp[6] = orig[idx - 1 - C1];
        tmp[7] = orig[idx - C1];
        sol[idx] = ((tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + tmp[7]) / delta);
      }
    }
  }
}