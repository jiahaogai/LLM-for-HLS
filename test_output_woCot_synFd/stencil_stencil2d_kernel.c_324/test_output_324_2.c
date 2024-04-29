#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int r;
  int c;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (r = 2; r < 128 - 1; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 2; c < 64 - 1; c++) {
      i = r * 64 + c;
      sol[i] = filter[0] * orig[i] + filter[1] * (orig[i - 1] + orig[i + 1]) + filter[2] * orig[i - 64] + filter[3] * (orig[i - 65] + orig[i + 64]) + filter[4] * (orig[i - 128] + orig[i + 128]) + filter[5] * (orig[i - 129] + orig[i + 127]) + filter[6] * orig[i - 2] + filter[7] * (orig[i - 3] + orig[i + 2]) + filter[8] * orig[i - 127] + filter[9] * (orig[i - 129] + orig[i + 127]);
    }
  }
}