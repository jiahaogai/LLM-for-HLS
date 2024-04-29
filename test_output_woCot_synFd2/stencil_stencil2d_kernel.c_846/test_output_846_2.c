#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8191; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{10}
      for (k = 0; k < 9; k++) {
        result += filter[k] * orig[i + ((k - 4) * 8191)];
      }
      sol[i * 8191 + j] = result;
    }
  }
}