#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 256; j++) {
      buf = 0.0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner_par:
      for (k_col = 0; k_col < 9; k_col++) {
        k = i + (k_col - 4);
        if (((k < 0) || (k >= 256))) {
          buf = 0.0;
        }
         else {
          buf += filter[k_col] * orig[k * 256 + j];
        }
      }
      sol[i * 256 + j] = buf;
    }
  }
}