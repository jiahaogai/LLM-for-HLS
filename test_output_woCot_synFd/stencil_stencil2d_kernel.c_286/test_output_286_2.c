#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 1; k < 33; k++) {
      i = (j - 1) * 32 + (k - 1);
      val = ((orig[i] + orig[i + 32]) + orig[i + 32 * 32]) + filter[0];
      val = (val + ((orig[i + 1] + orig[i + 32 + 1]) + orig[i + 32 * 32 + 1])) + filter[1];
      val = (val + ((orig[i + 32 * 2] + orig[i + 32 * 2 + 32]) + orig[i + 32 * (2 + 32)])) + filter[2];
      val = (val + ((orig[i + 32 * (1 + 0)] + orig[i + 32 * (1 + 32)]) + orig[i + 32 * (1 + 32 * 2)])) + filter[3];
      val = (val + ((orig[i + 32 * (0 + 0)] + orig[i + 32 * (0 + 32)]) + orig[i + 32 * (0 + 32 * 2)])) + filter[4];
      val = (val + ((orig[i - 32] + orig[i + 32 * (32 - 1)]) + orig[i + 32 * (32 - 1) * 32])) + filter[5];
      val = (val + ((orig[i - 1] + orig[i + 32 - 1]) + orig[i + 32 * (32 - 1) * 32 - 1])) + filter[6];
      val = (val + ((orig[i - 32 * 2] + orig[i + 32 * (32 - 1) * 2]) + orig[i + 32 * (1 + 32 - 1) * 2])) + filter[7];
      val = (val + ((orig[i - 32 * (32 - 1)] + orig[i + 32 * (32 - 1) * (32 - 1)]) + orig[i + 32 * ((32 - 1) * 2 - 1) * (32 - 1)])) + filter[8];
      sol[i] = val;
    }
  }
}