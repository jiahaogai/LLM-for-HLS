#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int t_out;
  int t_in;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      t_out = 0;
      inner:
      for (k = 0; k < 9; k++) {
        t_in = orig[i * 8 + j + ((k - 4) * 8)] ;
        t_out += filter[k] * t_in;
      }
      sol[i * 8 + j] = t_out;
    }
  }
}