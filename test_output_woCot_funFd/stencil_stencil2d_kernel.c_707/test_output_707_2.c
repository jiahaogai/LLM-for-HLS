#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int min_i;
  int max_i;
  int min_j;
  int max_j;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_x:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loop_y:
    for (j = 1; j < 8191; j++) {
      t = 0;
      min_i = i - 1;
      if (min_i < 0) {
        min_i = 0;
      }
      max_i = i + 1;
      if (max_i > 8191) {
        max_i = 8191;
      }
      min_j = j - 1;
      if (min_j < 0) {
        min_j = 0;
      }
      max_j = j + 1;
      if (max_j > 8191) {
        max_j = 8191;
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{1}
      loop_k:
      for (k = min_i; k < max_i; k++) {
        
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{8}
        loop_l:
        for (l = min_j; l < max_j; l++) {
          x = k * 8192 + l;
          t += orig[x] * filter[(((j - l) + 4) * 5) + ((i - k) + 4)];
        }
      }
      y = i * 8192 + j;
      sol[y] = t;
    }
  }
}