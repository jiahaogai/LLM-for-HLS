#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loopj:
  for (j = 8; j < 7104 - 8; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loopi:
    for (i = 8; i < 8192 - 8; i++) {
      idx0 = i - 8;
      idx1 = i - 7;
      idx2 = i - 6;
      idx3 = i - 5;
      idx4 = i - 4;
      idx5 = i - 3;
      idx6 = i - 2;
      idx7 = i - 1;
      idx8 = i + 1;
      idx = i;
      sum = 0;
      loopk:
      for (k = 8; k < 9; k++) {
        sum += filter[k] * orig[idx0 + k - 8];
      }
      sum += -128 * orig[idx];
      sol[idx] = sum;
    }
  }
}