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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      t_out = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      inner:
      for (k = -4; k < 5; k++) {
        t_in = 0;
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        int_in:
        for (tmp = 0; tmp < 8; tmp++) {
          t_in += orig[(((i + tmp) + 256) % 256) * 256 + ((j + k + 256) % 256)];
        }
        filter_in:
        for (tmp = 0; tmp < 9; tmp++) {
          t_out += filter[tmp] * t_in;
        }
      }
      sol[i * 256 + j] = t_out;
    }
  }
}