#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int elem;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 1; j < 8186; j++) {
      elem = ((8192 * (j - 1)) + i) - 1;
      sol[elem] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        sol[elem] += filter[k] * orig[((8192 * (k - 1)) + i) - 1];
      }
    }
  }
}