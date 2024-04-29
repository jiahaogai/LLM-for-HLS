#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8190; i++) {
    middle:
    for (j = 1; j < 8190; j++) {
      idx = (i * 8190) + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = 0; k < 9; k++) {
        int tmp_idx = (i + ((k / 3) - center)) * 8190 + j + ((k % 3) - center);
        if (tmp_idx >= 0 && tmp_idx < 8192) {
          sol[idx] += filter[k] * orig[tmp_idx];
        }
      }
    }
  }
}