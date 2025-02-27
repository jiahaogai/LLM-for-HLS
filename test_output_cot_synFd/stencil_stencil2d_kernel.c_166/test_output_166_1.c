#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 8192; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{8}
      inner:
      for (k = -4; k < 5; k++) {
        result += filter[4 + k] * orig[i + k * 8192];
      }
      sol[i * 8192 + j] = result;
    }
  }
}