#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center;
  int flatten_idx;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 128 + 2; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 128 + 2; j++) {
      center = orig[i * (128 + 2) + j];
      flatten_idx = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      inner:
      for (k = 0; k < 9; k++) {
        idx = i * 9 + k;
        if ((((i == 0) || (i == 128 + 1)) || (j == 0)) || (j == 128 + 1)) {
          sol[idx] = 0;
        }
         else {
          sol[idx] = filter[k] * center + ((filter[k + 1] + filter[k - 1]) * orig[(((i - 1) * (128 + 2)) + j) - 1] + ((filter[k + 9] + filter[k - 9]) * orig[(((i - 1) * (128 + 2)) + j) + 1]) - ((filter[k + 10] + filter[k - 10]) * center));
        }
      }
    }
  }
}