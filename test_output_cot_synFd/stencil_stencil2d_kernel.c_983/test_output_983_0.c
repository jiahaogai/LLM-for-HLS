#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 1; j < 337; j++) {
      idx = i * 337 + j;
      sol[idx] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int temp_idx = idx - 4 + k;
        if (temp_idx < 0) {
          temp_idx = -temp_idx;
        }
        
#pragma ACCEL PIPELINE auto{off}
        if (temp_idx > 8191) {
          temp_idx = 8191;
        }
        sol[idx] += filter[k] * orig[temp_idx];
      }
    }
  }
}