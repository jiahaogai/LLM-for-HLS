#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buf;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{2}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      buf = 0.0;
      
#pragma ACCEL PARALLEL reduction=buf FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k / 3) - 1);
        int orig_index = (k_col < 0) ? 0 : (k_col >= 256 ? 255 : k_col);
        int filter_index = (k % 3) - 1;
        int filter_index_tmp = (filter_index < 0) ? 0 : (filter_index >= 3 ? 2 : filter_index);
        buf += orig[orig_index * 256 + j] * filter[filter_index_tmp];
      }
      sol[i * 256 + j] = buf;
    }
  }
}