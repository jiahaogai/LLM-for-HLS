#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 8192; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{8}
      middle:
      for (k = -45; k <= 45; k++) {
        if ((i + 45 > -1) && (i + 45 < 8192) && (j + k > -1) && (j + k < 8192)) {
          result += orig[i + 45 + ((j + k) * 8192)] * filter[45 + k];
        }
      }
      sol[i * 8192 + j] = result;
    }
  }
}