#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      if (k < 0) {
        k = 0;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (j = 0; j < 9; j++) {
        k = i - 4 + j;
        if (k < 0) {
          k = 0;
        }
        if (k > 8191) {
          k = 8191;
        }
        result += ((int )filter[j]) * orig[k];
      }
    }
    sol[i] = result;
    result = 0;
  }
}