#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
    for (j = 0; j < 256; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        result += orig[i * 256 + j] * filter[k];
      }
      sol[i * 256 + j] = result;
    }
  }
}