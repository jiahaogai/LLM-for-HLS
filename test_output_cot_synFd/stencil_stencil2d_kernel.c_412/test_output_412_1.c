#pragma ACCEL kernel

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
  outer:
  for (i = 1; i < 8191; i++) {
    middle:
    for (j = 1; j < 8191; j++) {
      idx = i * 8191 + j;
      val = orig[idx] + filter[0] * orig[idx - 8191 + 1] + filter[1] * orig[idx - 8191] + filter[2] * orig[idx - 8191 - 1] + filter[3] * orig[idx + 1] + filter[4] * orig[idx] + filter[5] * orig[idx - 1] + filter[6] * orig[idx + 8191] + filter[7] * orig[idx + 8191 + 1];
      sol[idx] = val;
    }
  }
}