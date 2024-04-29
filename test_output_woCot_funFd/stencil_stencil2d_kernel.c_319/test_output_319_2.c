#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8186; j++) {
      idx = (i - 1) * 8186 + j - 1;
      sol[idx] = ((filter[0] * orig[idx - 8186 - 1]) + (filter[1] * orig[idx - 8186]) + (filter[2] * orig[idx - 8186 + 1])) + ((filter[3] * orig[idx - 1]) + (filter[4] * orig[idx]) + (filter[5] * orig[idx + 1])) + ((filter[6] * orig[idx + 8186 - 1]) + (filter[7] * orig[idx + 8186]) + (filter[8] * orig[idx + 8186 + 1]));
    }
  }
}