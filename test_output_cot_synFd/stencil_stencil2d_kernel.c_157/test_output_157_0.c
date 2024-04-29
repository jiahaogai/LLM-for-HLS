#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{16}
 void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128 - 1; j++) {
      idx = i * 128 + j;
      center = orig[idx];
      sol[idx] = ((filter[0] * center) + (filter[1] * (center + orig[idx + 1])) + (filter[2] * (center + orig[idx + 1 * 128]))) + ((filter[3] * (center + orig[idx - 1])) + (filter[4] * (center + orig[idx + 1 - 128])));
    }
  }
}