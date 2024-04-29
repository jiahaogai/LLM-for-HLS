#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{7}
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
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    for (j = 1; j < 8188; j++) {
      idx = 8192 * (i - 1) + (j - 1);
      val = orig[idx] + filter[0] * orig[idx - 8192 - 1] + filter[1] * orig[idx - 8192] + filter[2] * orig[idx - 8192 + 1] + filter[3] * orig[idx - 1] + filter[4] * orig[idx + 1] + filter[5] * orig[idx + 8192 - 1] + filter[6] * orig[idx + 8192] + filter[7] * orig[idx + 8192 + 1];
      sol[idx] = val;
    }
  }
}