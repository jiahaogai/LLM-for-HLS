#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int x;
  int y;
  int t;
  int ft[9];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 64 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 128 - 1; j++) {
      idx = i * 128 + j;
      x = orig[idx - 128] + 2 * orig[idx] + orig[idx + 128];
      y = orig[idx - 1] + 2 * orig[idx] + orig[idx + 1];
      t = 0;
      ft[0] = x + y;
      ft[1] = x - y;
      ft[2] = x + 2 * y;
      ft[3] = x - 2 * y;
      ft[4] = x + 3 * y;
      ft[5] = x - 3 * y;
      ft[6] = x + 4 * y;
      ft[7] = x - 4 * y;
      ft[8] = x + 5 * y;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        t += filter[k] * ft[k];
      }
      sol[idx] = t;
    }
  }
}