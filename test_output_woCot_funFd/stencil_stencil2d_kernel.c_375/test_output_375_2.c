Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      tmp = ((filter[0] * orig[idx]) + (filter[1] * orig[idx + 1]) + (filter[2] * orig[idx + 2])) + ((filter[3] * orig[idx + 256]) + (filter[4] * orig[idx + 257]) + (filter[5] * orig[idx + 258])) + ((filter[6] * orig[idx + 512]) + (filter[7] * orig[idx + 513]) + (filter[8] * orig[idx + 514]));
      tmp = tmp < 0 ? 0 : tmp;
      tmp = tmp > 255 ? 255 : tmp;
      sol[idx] = tmp;
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer_1:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle_1:
    for (j = 0; j < 256; j++) {
      idx = i * 256 + j;
      tmp = ((filter[0] * sol[idx]) + (filter[1] * sol[idx + 1]) + (filter[2] * sol[idx + 2])) + ((filter[3] * sol[idx + 256]) + (filter[4] * sol[idx + 257]) + (filter[5] * sol[idx + 258])) + ((filter[6] * sol[idx + 512]) + (filter[7] * sol[idx + 513]) + (filter[8] * sol[idx + 514]));
      tmp = tmp < 0 ? 0 : tmp;
      tmp = tmp > 255 ? 255 : tmp;
      orig[idx] = tmp;
    }
  }
}