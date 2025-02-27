#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8186; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{1}
      inner:
      for (k = -4; k <= 4; k++) {
        tmp += filter[4 + k] * orig[i + k * 8192];
      }
      sol[i * 8192 + j] = tmp;
    }
  }
}