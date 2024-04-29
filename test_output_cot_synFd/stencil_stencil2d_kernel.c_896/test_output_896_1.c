#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    for (j = 0; j < 8192; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = -45; k <= 45; k++) {
        if ((((i + k) >= 0) && ((i + k) < 8192)) && ((j >= 0) && (j < 8192))) {
          result += orig[((i + k) * 8192) + j] * filter[k + 45];
        }
      }
      sol[i * 8192 + j] = result;
    }
  }
}