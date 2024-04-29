#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int upper_bound;
  int lower_bound;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    sum = 0.0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 9; j++) {
      upper_bound = (8192 + 9) / 2;
      lower_bound = (8192 - 9) / 2;
      if (i > upper_bound) {
        k = i - 8;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      else if (i < lower_bound) {
        k = i + 8;
      }
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      else {
        k = i;
      }
      sum += filter[j] * orig[k];
    }
    sol[i] = sum;
  }
}