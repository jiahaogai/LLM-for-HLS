Code: #pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 32; j++) {
      idx = i * 32 + j;
      val = ((filter[0] * orig[idx - 9]) + (filter[1] * orig[idx - 8]) + (filter[2] * orig[idx - 7])) + ((filter[3] * orig[idx - 6]) + (filter[4] * orig[idx - 5]) + (filter[5] * orig[idx - 4])) + ((filter[6] * orig[idx - 3]) + (filter[7] * orig[idx - 2]) + (filter[8] * orig[idx - 1]));
//#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      val = val + orig[idx];
      sol[idx] = val;
    }
  }
}