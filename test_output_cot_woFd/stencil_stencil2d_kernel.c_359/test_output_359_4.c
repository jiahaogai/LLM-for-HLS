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
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 9; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        tmp += orig[i + k] * filter[j + k];
      }
      sol[i + 4] = tmp;
    }
  }
}