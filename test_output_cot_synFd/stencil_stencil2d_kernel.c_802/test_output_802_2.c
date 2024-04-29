#pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 1; j < 8190; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
    for (i = 1; i < 8190; i++) {
      sum = filter[0] * orig[i + 8190 * j];
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{4}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      loopk:
      for (k = 1; k < 9; k++) {
        idx = i + (-8190 + k);
        if (idx >= 1 && idx <= 8190) {
          sum += filter[k] * orig[idx + 8190 * j];
        }
      }
      sol[i + 8190 * j] = sum;
    }
  }
}