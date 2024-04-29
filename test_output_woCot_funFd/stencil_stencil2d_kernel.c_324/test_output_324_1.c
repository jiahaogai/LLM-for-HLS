#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 128 + 2; j++) {
      idx = i * (128 + 2) + j;
      val = orig[idx] * filter[0];
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 1; k < 9; k++) {
        idx = (i + (k - 1)) * (128 + 2) + j;
        val += orig[idx] * filter[k];
      }
      sol[idx] = val;
    }
  }
}