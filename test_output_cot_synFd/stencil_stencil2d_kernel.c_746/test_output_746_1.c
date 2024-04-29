#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopk:
    for (k = 1; k < 33; k++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL reduction=s FACTOR=auto{1}
      loopi:
      for (i = 1; i < 33; i++) {
        idx = i * 33 + j * 33 * 32 + k;
        s += ((double )filter[0]) * orig[idx - 1] + ((double )filter[1]) * orig[idx] + ((double )filter[2]) * orig[idx + 1] + ((double )filter[3]) * orig[idx - 33] + ((double )filter[4]) * orig[idx + 33] + ((double )filter[5]) * orig[idx - 33 * 32] + ((double )filter[6]) * orig[idx + 33 * 32] + ((double )filter[7]) * orig[idx - 1 - 33 * 32] + ((double )filter[8]) * orig[idx + 1 - 33 * 32];
      }
      sol[idx] = s;
    }
  }
}