#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{2}
      inner:
      for (k = 0; k < 9; k++) {
        tmp += filter[k] * orig[i + k - 4 + ((j + k - 4) * 8192)];
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}