#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{2}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 1; i < 8191; i++) {
    middle:
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int temp;
        int filter_idx;
        filter_idx = k + center;
        if (filter_idx < 0) {
          filter_idx += 9;
        }
        else {
          if (filter_idx > 8) {
            filter_idx -= 9;
          }
        }
        temp = filter[k] * orig[idx + filter_idx * 8192];
        sol[idx] += temp;
      }
    }
  }
}