The following C code implements the stencil function:
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 8; j < 8176; j += 8) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; ++k) {
        tmp += filter[k] * orig[i + k - 4];
      }
      sol[j] = tmp;
    }
  }
}