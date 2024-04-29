#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int t;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    t = orig[i] * filter[0];
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{31}
    middle:
    for (j = 1; j < 9; j++) {
      t += orig[i + j] * filter[j];
    }
    sum = t;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 1; j < 9; j++) {
      t = orig[i] * filter[j];
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{2}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_1:
      for (k = 1; k < 9; k++) {
        t += orig[i + k] * filter[k * 9 + j];
      }
      sol[i + j] = sum - t;
    }
    sol[i] = sum;
  }
}