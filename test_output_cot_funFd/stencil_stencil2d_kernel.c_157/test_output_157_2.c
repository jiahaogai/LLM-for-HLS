#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 4;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 128 + 1 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 64 + 1 - 1; j++) {
      idx = i * 64 + j;
      sol[idx] = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[idx] += filter[k] * orig[idx + ((k - 4) * 64)];
      }
    }
  }
}