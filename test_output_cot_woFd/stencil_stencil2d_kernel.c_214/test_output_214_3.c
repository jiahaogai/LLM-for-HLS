#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 64; j++) {
      result = ((filter[0] * orig[i * 64 + j]) + (filter[1] * orig[i * 64 + j + 1]) + (filter[2] * orig[i * 64 + j + 2]) + (filter[3] * orig[i * 64 + j + 64]) + (filter[4] * orig[i * 64 + j + 65]) + (filter[5] * orig[i * 64 + j + 66]) + (filter[6] * orig[i * 64 + j + 128]) + (filter[7] * orig[i * 64 + j + 129]) + (filter[8] * orig[i * 64 + j + 130]));
      sol[i * 64 + j] = result;
    }
  }
}