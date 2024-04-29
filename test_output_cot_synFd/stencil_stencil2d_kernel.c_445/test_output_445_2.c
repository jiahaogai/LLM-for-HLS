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
      val = orig[i] * filter[0];
      idx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop1:
      for (int _in_idx1 = 1; _in_idx1 < 9; _in_idx1++) {
        idx++;
        val += orig[i + _in_idx1] * filter[idx];
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop2:
      for (int _in_idx2 = -1; _in_idx2 > -9; _in_idx2--) {
        val += orig[i + _in_idx2] * filter[idx];
        idx--;
      }
      sol[i] = val;
    }
  }
}