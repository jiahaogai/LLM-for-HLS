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
    result = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    inner:
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      if (k < 0 || k > 8191) {
        result += 0;
      }
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      middle:
      for (j = 0; j < 1; j++) {
        if (k < 0 || k > 8191) {
          result += 0;
        }
        else {
          result += orig[k] * filter[j];
        }
      }
    }
    sol[i] = result;
  }
}