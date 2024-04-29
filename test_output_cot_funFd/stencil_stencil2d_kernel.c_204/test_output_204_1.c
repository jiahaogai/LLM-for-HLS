#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{1}
      loopk:
      for (k = 0; k < 9; k++) {
        idx = (((32 + 2) * (j - 1)) + (i - 1)) * 32 + k - 4;
        s += ((double )filter[k]) * orig[idx];
      }
      sol[(((32 + 2) * (j - 1)) + (i - 1)) ] = s;
    }
  }
}