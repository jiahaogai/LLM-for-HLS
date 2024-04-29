#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int val0;
  int val1;
  int val2;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 128; j++) {
      idx0 = ((i - 1) * 128) + (j - 1);
      idx1 = ((i - 1) * 128) + j;
      idx2 = ((i - 1) * 128) + (j + 1);
      val0 = orig[idx0];
      val1 = orig[idx1];
      val2 = orig[idx2];
      idx = i * 128 + j;
      sol[idx] = filter[0] * val0 + filter[1] * val1 + filter[2] * val2;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 1; k < 8; k++) {
        idx0 = idx0 + 128;
        idx1 = idx1 + 128;
        idx2 = idx2 + 128;
        val0 = orig[idx0];
        val1 = orig[idx1];
        val2 = orig[idx2];
        sol[idx] += filter[k] * val0 + filter[8 - k] * val1 + val2;
      }
    }
  }
}