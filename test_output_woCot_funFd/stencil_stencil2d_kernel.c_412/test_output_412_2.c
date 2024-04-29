Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 1; j < 8186; j++) {
      idx = (i * 8186) + j;
      val = ((orig[idx + 798] + orig[idx - 798]) + (orig[idx + 1] + orig[idx - 1])) + (orig[idx + 79] + orig[idx - 79]) + (orig[idx + 8] + orig[idx - 8]) + orig[idx];
      sol[idx] = val;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 1; j < 8186; j++) {
      idx = (i * 8186) + j;
      sol[idx] = (((sol[idx + 798] + sol[idx - 798]) + (sol[idx + 1] + sol[idx - 1])) + (sol[idx + 79] + sol[idx - 79])) + (sol[idx + 8] + sol[idx - 8]) + (filter[4] * sol[idx]);
    }
  }
}