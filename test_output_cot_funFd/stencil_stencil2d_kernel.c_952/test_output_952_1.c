Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8192; j++) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = -45; k < -36; k++) {
        tmp += orig[i + k] * filter[k + 36];
      }
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for ( ; k < -16; k++) {
        tmp += orig[i + k] * filter[k + 36];
      }
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for ( ; k < 0; k++) {
        tmp += orig[i + k] * filter[k + 36];
      }
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for ( ; k < 16; k++) {
        tmp += orig[i + k] * filter[k + 36];
      }
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for ( ; k < 36; k++) {
        tmp += orig[i + k] * filter[k + 36];
      }
      sol[i + 4] = tmp;
    }
  }
}