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
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 1; k < 33; k++) {
      i = (j - 1) * 32 + k - 1;
      val = orig[i] * filter[0];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopidx:
      for (idx = 1; idx < 9; idx++) {
        val += orig[i + idx] * filter[idx];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopidxj:
      for (idx = -1; idx > -33; idx--) {
        val += orig[i + idx] * filter[idx];
      }
      sol[i] = val;
    }
  }
}