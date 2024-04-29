#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopk:
    for (k = 1; k < 33; k++) {
      i = (j - 1) * 32 + k - 1;
      val = ((orig[i] << 6) + filter[0]) + ((orig[i + 1] << 5) + filter[1]) + ((orig[i + 32] << 2) + filter[2]) + ((orig[i + 33] >> 2) + filter[3]) + ((orig[i + 32 + 1] >> 6) + filter[4]);
      sol[i] = val;
    }
  }
}