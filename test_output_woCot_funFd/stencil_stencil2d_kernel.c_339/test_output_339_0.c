#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      result = ((filter[0] * orig[i * 256 + j]) + (filter[1] * orig[i * 256 + j + 1]) + (filter[2] * orig[i * 256 + j + 2]) + (filter[3] * orig[i * 256 + j + 256]) + (filter[4] * orig[i * 256 + j + 257]) + (filter[5] * orig[i * 256 + j + 258]) + (filter[6] * orig[i * 256 + j + 1 + 256]) + (filter[7] * orig[i * 256 + j + 1 + 257]) + (filter[8] * orig[i * 256 + j + 1 + 258]));
      sol[i * 256 + j] = result;
    }
  }
}