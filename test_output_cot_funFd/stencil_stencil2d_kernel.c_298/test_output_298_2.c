#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 0; i < 64; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 64; j++) {
      idx = i * 64 + j;
      inner:
      for (k = 0; k < 9; k++) {
        if ((((4 + (k / 3)) - center) + i) >= 0 && (((4 + (k / 3)) - center) + i) < 64 && (((4 + (k % 3)) - center) + j) >= 0 && (((4 + (k % 3)) - center) + j) < 64) {
          sol[idx] += filter[k] * orig[(((4 + (k / 3)) - center) + i) * 64 + ((4 + (k % 3)) - center) + j];
        }
      }
    }
  }
}