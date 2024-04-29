#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int centered_idx;
  int flattened_idx;
  int filtered_val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_i:
  for (i = 1; i < 33; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 33; j++) {
      idx = i * 32 + j;
      centered_idx = (i - 1) * 32 + (j - 1);
      flattened_idx = centered_idx;
//#pragma ACCEL PARALLEL reduction = sol FACTOR=auto{8}
      loop_k:
      for (k = 0; k < 9; k++) {
        filtered_val = orig[centered_idx + filter[k]];
        sol[flattened_idx] += filtered_val * filter[k];
      }
    }
  }
}