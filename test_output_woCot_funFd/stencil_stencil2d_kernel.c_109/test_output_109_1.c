#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

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
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopk:
    for (k = 1; k < 8191; k++) {
      idx = (8192 + 1) * j + k;
      val = ((orig[idx - 8192] + orig[idx - 8191]) + orig[idx - 1]) + ((orig[idx + 1] + orig[idx + 8191]) + orig[idx + 8192]);
      sol[idx] = val;
    }
  }
}