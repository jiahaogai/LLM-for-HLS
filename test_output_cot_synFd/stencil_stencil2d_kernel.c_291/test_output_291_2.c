#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int centered_idx;
  int left_idx;
  int right_idx;
  int up_idx;
  int down_idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 1; j < 128 - 1; j++) {
      idx = i * 128 + j;
      centered_idx = idx + 128;
      left_idx = idx - 1;
      right_idx = idx + 1;
      up_idx = idx - 128;
      down_idx = idx + 128;
      sol[idx] = ((filter[0] * orig[centered_idx]) + (filter[1] * (orig[left_idx] + orig[right_idx])) + (filter[2] * (orig[up_idx] + orig[down_idx]))) - (filter[3] * orig[idx]);
    }
  }
}