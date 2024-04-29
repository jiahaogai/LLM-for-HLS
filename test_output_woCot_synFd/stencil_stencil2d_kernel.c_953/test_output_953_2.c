#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  loopj:
  for (j = 1; j < 64 + 1 - 4; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = 1; i < 128 + 1 - 4; i++) {
      idx = i + j * 128;
      center = orig[idx];
      flatten_idx = 0 + filter[0] * idx;
      sol[idx] = center + ((filter[flatten_idx + 1] * orig[idx + 1]) + (filter[flatten_idx + 2] * orig[idx + 2]) + (filter[flatten_idx + 3] * orig[idx + 1 + 128]) + (filter[flatten_idx + 4] * orig[idx + 2 + 128]) + (filter[flatten_idx + 5] * orig[idx + 1 + 128 + 128]) + (filter[flatten_idx + 6] * orig[idx + 2 + 128 + 128]) + (filter[flatten_idx + 7] * orig[idx + 1 + 128 + 128 + 128]) + (filter[flatten_idx + 8] * orig[idx + 2 + 128 + 128 + 128]));
    }
  }
}