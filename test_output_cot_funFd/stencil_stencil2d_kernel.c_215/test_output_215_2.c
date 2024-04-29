#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0;
      inner:
      for (k = -4; k < 5; k++) {
        idx = (i * 256 + j) * 256 + k;
        if ((((i * 256 + j) * 256 + k) >= 0 && ((i * 256 + j) * 256 + k) < 8192)) {
          sum += orig[idx] * filter[k + 4];
        }
      }
      sol[i * 256 + j] = sum;
    }
  }
}