#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
    for (j = 0; j < 8192; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{16}
      for (k = 0; k < 9; k++) {
        result += orig[i + k - 4] * filter[k];
      }
      sol[j] = result;
    }
  }
}