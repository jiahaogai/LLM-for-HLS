#pragma ACCEL kernel

void stencil(int orig[8192][8192],int sol[8192][8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_loc;
  int max_loc;
  int range;
  int min;
  int max;
  range = 1 + 8;
  max = -32768;
  min = 32767;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      t = ((filter[0] * orig[i - 1][j - 1]) + (filter[1] * orig[i - 1][j]) + (filter[2] * orig[i - 1][j + 1]) + (filter[3] * orig[i][j - 1]) + (filter[4] * orig[i][j]) + (filter[5] * orig[i][j + 1]) + (filter[6] * orig[i + 1][j - 1]) + (filter[7] * orig[i + 1][j]) + (filter[8] * orig[i + 1][j + 1])) >> 4;
      if (t > max) {
        max = t;
        max_loc = i;
      }
      if (t < min) {
        min = t;
        min_loc = i;
      }
      sol[i][j] = t;
    }
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      orig[i][j] = sol[max_loc][j];
      max_loc = min_loc;
      min_loc = i;
      if (max < min) {
        t = max;
        max = min;
        min = t;
      }
    }
  }
}