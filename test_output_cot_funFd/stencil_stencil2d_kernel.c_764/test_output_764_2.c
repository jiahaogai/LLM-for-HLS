#pragma ACCEL kernel

void stencil(double orig[8192],double sol[8192],double filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int i_col;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    middle:
    for (j = 1; j < 8191; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = ((i + (-4 + ((k >> 6) & 3)))) - 1;
        i_col = ((j + (-4 + ((k << 3) & 7)))) - 1;
        if ((((k_col << 11) | (i_col << 1)) << 3) < 65536) {
          sum += filter[k] * orig[(((k_col << 11) | (i_col << 1)) << 3)] ;
        }
      }
      sol[(((i << 11) | (j << 1)) << 3)] = sum;
    }
  }
}