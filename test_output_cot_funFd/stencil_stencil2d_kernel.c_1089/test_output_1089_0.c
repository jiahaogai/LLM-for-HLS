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
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{7}
      for (k = -4; k < 5; k++) {
        int cur;
        int left;
        int right;
        int up;
        int down;
        cur = orig[i * 64 + j * 8 + k + pad];
        left = orig[i * 64 + j * 8 + k * 1 - 1 + pad];
        right = orig[i * 64 + j * 8 + k * 1 + 1 + pad];
        up = orig[(i * 64 + j * 8 + k * 8 - 8) + pad];
        down = orig[(i * 64 + j * 8 + k * 8 + 8) + pad];
        t += filter[k + 4] * cur;
        t += filter[k + 4] * left;
        t += filter[k + 4] * right;
        t += filter[k + 4] * up;
        t += filter[k + 4] * down;
      }
      sol[i * 64 + j * 8 + pad] = t;
    }
  }
}