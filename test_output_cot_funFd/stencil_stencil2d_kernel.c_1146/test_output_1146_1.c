#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      ti = i - 4 + ((0 > (i - 4)) ? 0 : ((8192 < (i - 4)) ? 8191 : (i - 4)));
      tj = j - 4 + ((0 > (j - 4)) ? 0 : ((8192 < (j - 4)) ? 8191 : (j - 4)));
      idx = ti * 8192 + tj;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{2}
      inner:
      for (int k = 0; k < 9; ++k) {
        val += filter[k] * orig[idx + offset[k].i] * offset[k].j;
      }
      sol[i * 8192 + j] = val;
    }
  }
}