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
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx0 = i * 256 + j;
      idx1 = i * 16 + 8 + j;
      idx2 = i * 16 + j;
      val = orig[idx0] + filter[0] * orig[idx1] + filter[1] * orig[idx1 + 1] + filter[2] * orig[idx1 + 16] + filter[3] * orig[idx1 + 17] + filter[4] * orig[idx1 + 16 * 2] + filter[5] * orig[idx1 + 17 * 2] + filter[6] * orig[idx1 + 16 * 3] + filter[7] * orig[idx1 + 17 * 3] + filter[8] * orig[idx2];
      sol[idx0] = val;
    }
  }
}