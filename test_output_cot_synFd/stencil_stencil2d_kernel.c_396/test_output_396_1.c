#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int index;
  int flatten_index;
  int range_l;
  int range_r;
  int tid;
  int pid;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  loop_l1:
/* Standardize from: for(i = 1; i < 8191; i++) {...} */
  for (i = 1 + 8191 * 0; i < 8191 + 8191 * 1; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loop_l2:
/* Standardize from: for(j = 1; j < 8191; j++) {...} */
    for (j = 1 + 8191 * 0; j < 8191 + 8191 * 0; j++) {
      flatten_index = i * 8191 + j;
      range_l = (flatten_index < 8191) ? flatten_index : 8191;
      range_r = (flatten_index < 8191) ? 0 : flatten_index - 8191;
      index = 4 * range_l + range_r;
      sol[flatten_index] = ((filter[0] * orig[index]) + (filter[1] * orig[index + 1]) + (filter[2] * orig[index + 8191]) + (filter[3] * orig[index + 8192]) + (filter[4] * orig[index + 8191 + 1]) + (filter[5] * orig[index + 8192 + 1]) + (filter[6] * orig[index + 8191 - 1]) + (filter[7] * orig[index + 8192 - 1]) + (filter[8] * orig[index + 1 - 8191])) / 8192;
    }
  }
}