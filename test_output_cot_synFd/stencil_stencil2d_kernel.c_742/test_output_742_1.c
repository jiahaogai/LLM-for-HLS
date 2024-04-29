#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int index;
  int flatten_index;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 32; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 32; j++) {
      tmp = 0;
      inner:
      for (k = 0; k < 9; k++) {
        index = (((32 + 2) * (32 + 2)) * i) + (((32 + 2) * j) + k);
        flatten_index = ((9 * i) + k) + (32 * j);
        tmp += filter[k] * orig[index];
      }
      sol[flatten_index] = tmp;
    }
  }
}