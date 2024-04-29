#pragma ACCEL kernel

void kernel(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int t;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0;
      inner:
      for (k = 0; k < 9; k++) {
        t = i + ((k / 3) - 1);
        if (((t >= 0) && (t < 256))) {
          t = j + ((k % 3) - 1);
          if (((t >= 0) && (t < 256))) {
            sum += orig[t] * filter[k];
          }
        }
      }
      sol[j] = sum;
    }
    for (j = 0; j < 256; j++) {
      orig[j] = sol[j];
    }
  }
}