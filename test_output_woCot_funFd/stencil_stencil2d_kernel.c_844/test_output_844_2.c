#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
    for (j = 0; j < 8192; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{2}
      for (k = -4; k < 5; k++) {
        int cur;
        int left;
        int right;
        int up;
        int down;
        cur = orig[i * 8192 + j];
        left = (j == 0) ? 0 : orig[i * 8192 + (j - 1)];
        right = (j == 8191) ? 0 : orig[i * 8192 + (j + 1)];
        up = (i == 0) ? 0 : orig[(i - 1) * 8192 + j];
        down = (i == 8191) ? 0 : orig[(i + 1) * 8192 + j];
        t += filter[k + 4] * cur + filter[k + 4] * left + filter[k + 4] * right + filter[k + 4] * up + filter[k + 4] * down;
      }
      sol[i * 8192 + j] = t;
    }
  }
}