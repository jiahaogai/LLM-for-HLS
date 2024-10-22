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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 1; i < 337; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 337; j++) {
      s = 0.0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idx = (i + (-1 + k)) * 337 + j + (-1 + k);
        if (idx < 0) {
          idx = 0;
        }
        else {
          if (idx > 8191) {
            idx = 8191;
          }
        }
        s += ((double )filter[k]) * orig[idx];
      }
      sol[i * 337 + j] = s;
    }
  }
}