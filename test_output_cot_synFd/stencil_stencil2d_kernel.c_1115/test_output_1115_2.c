Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8192; i++) {
    idx = i - 4;
    center = orig[i] - ((filter[0] * orig[idx + 0]) + (filter[1] * orig[idx + 1]) + (filter[2] * orig[idx + 2]) + (filter[3] * orig[idx + 3]) + (filter[4] * orig[idx + 4]) + (filter[5] * orig[idx + 5]) + (filter[6] * orig[idx + 6]) + (filter[7] * orig[idx + 7]) + (filter[8] * orig[idx + 8]));
    sol[i] = center;
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    idx = i - 4;
    center = sol[i] - ((filter[0] * sol[idx + 0]) + (filter[1] * sol[idx + 1]) + (filter[2] * sol[idx + 2]) + (filter[3] * sol[idx + 3]) + (filter[4] * sol[idx + 4]) + (filter[5] * sol[idx + 5]) + (filter[6] * sol[idx + 6]) + (filter[7] * sol[idx + 7]) + (filter[8] * sol[idx + 8]));
    sol[i] = center;
  }
}