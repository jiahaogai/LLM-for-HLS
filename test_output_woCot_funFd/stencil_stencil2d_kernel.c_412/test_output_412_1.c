Code: #pragma ACCEL kernel

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
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8186; j++) {
      idx = (i * 8186) + j;
      val = 0;
      k = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      while (k < 9) {
        val += filter[k] * orig[idx + (-8186 + k)];
        k++;
      }
      sol[idx] = val;
    }
  }
}