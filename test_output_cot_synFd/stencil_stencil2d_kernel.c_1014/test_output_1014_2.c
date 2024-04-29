Code: ## ACCEL kernel

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int row;
  int col;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        row = i + k;
        inner_middle:
        for (col = -4; col < 5; col++) {
          int orig_idx = row * 256 + col;
          int filter_idx = (k + 4) * 5 + (col + 4);
          t += orig[orig_idx] * filter[filter_idx];
        }
      }
      sol[i * 256 + j] = t;
    }
  }
}