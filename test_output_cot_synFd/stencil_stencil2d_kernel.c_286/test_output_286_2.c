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
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk:
    for (k = 1; k < 33; k++) {
      i = (j - 1) * 32 + k - 1;
      val = ((0 + filter[0]) * orig[i]) + ((0 + filter[1]) * orig[i + 1]) + ((0 + filter[2]) * orig[i + 32]) + ((0 + filter[3]) * orig[i + 33]) + ((0 + filter[4]) * orig[i + 32 + 1]) + ((0 + filter[5]) * orig[i + 33 + 1]) + ((0 + filter[6]) * orig[i + 32 - 1]) + ((0 + filter[7]) * orig[i + 33 - 1]) + ((0 + filter[8]) * orig[i]);
      sol[i] = val;
    }
  }
}