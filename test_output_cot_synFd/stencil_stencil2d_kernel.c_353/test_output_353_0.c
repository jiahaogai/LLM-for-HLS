#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    middle:
    for (j = 0; j < 9; j++) {
      sum = 0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = -4; k < 5; k++) {
        sum += filter[j] * orig[i + k];
      }
      sol[i + 4] = sum;
    }
  }
}