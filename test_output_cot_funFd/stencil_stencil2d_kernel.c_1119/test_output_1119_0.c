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
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{7}
    for (j = 1; j < 8188; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = -4; k <= 4; k++) {
        idx = (i - 1) * 8188 + j + k;
        if (idx < 0) {
          idx = 0;
        }
        else if (idx > 8188 * 8190) {
          idx = 8188 * 8190;
        }
        s += orig[idx] * filter[k + 4];
      }
      sol[i * 8188 + j] = s;
    }
  }
}