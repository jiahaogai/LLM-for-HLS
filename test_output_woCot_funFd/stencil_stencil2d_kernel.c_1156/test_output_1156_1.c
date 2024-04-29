#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 1; i < 128 + 1 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 64 + 1 - 1; j++) {
      s = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      for (k = 0; k < 9; k++) {
        idx = ((((64 + 1 - 1) * (128 + 1 - 1)) * k) + (((128 + 1 - 1) * j) - 1)) + i - 1;
        s += ((double )filter[k]) * orig[idx];
      }
      sol[(((64 + 1 - 1) * (128 + 1 - 1)) * i) + j - 1] = s;
    }
  }
}