#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  loopj:
  for (j = 1; j < 8191; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8191; i++) {
      idx = i + j * 8192;
      sol[idx] = ((filter[0] * orig[idx - 8192]) + (filter[1] * orig[idx - 8191]) + (filter[2] * orig[idx - 8190]) + (filter[3] * orig[idx - 8189]) + (filter[4] * orig[idx - 8188]) + (filter[5] * orig[idx - 8187]) + (filter[6] * orig[idx - 8186]) + (filter[7] * orig[idx - 8185]) + (filter[8] * orig[idx - 8184])) +
                 ((filter[0 + 8] * orig[idx + 8 - 8192]) + (filter[1 + 8] * orig[idx + 8 - 8191]) + (filter[2 + 8] * orig[idx + 8 - 8190]) + (filter[3 + 8] * orig[idx + 8 - 8189]) + (filter[4 + 8] * orig[idx + 8 - 8188]) + (filter[5 + 8] * orig[idx + 8 - 8187]) + (filter[6 + 8] * orig[idx + 8 - 8186]) + (filter[7 + 8] * orig[idx + 8 - 8185]) + (filter[8 + 8] * orig[idx + 8 - 8184]));
    }
  }
}