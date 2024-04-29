#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    inner:
    for (j = 0; j < 64 + 2; j++) {
      result = ((0 + filter[0]) * orig[i * (64 + 2) + j]) + ((0 + filter[1]) * orig[i * (64 + 2) + j + 1]) + ((0 + filter[2]) * orig[i * (64 + 2) + j + 2]) + ((1 + filter[3]) * orig[i * (64 + 2) + j + 1 + 1]) + ((2 + filter[4]) * orig[i * (64 + 2) + j + 2 + 1]) + ((1 + filter[5]) * orig[i * (64 + 2) + j + 1 + 2]) + ((2 + filter[6]) * orig[i * (64 + 2) + j + 2 + 2]) + ((1 + filter[7]) * orig[i * (64 + 2) + j + 1 + 1]) + ((0 + filter[8]) * orig[i * (64 + 2) + j + 2 + 1]);
      sol[i * (64 + 2) + j] = result;
    }
  }
}