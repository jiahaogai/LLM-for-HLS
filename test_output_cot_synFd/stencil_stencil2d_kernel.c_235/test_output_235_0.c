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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8186; j++) {
      idx = i * 8186 + j;
      sol[idx] = ((filter[0] * orig[idx - 46]) + (filter[1] * orig[idx - 23]) + (filter[2] * orig[idx]) + (filter[3] * orig[idx + 23]) + (filter[4] * orig[idx + 46])) / 256;
    }
  }
}