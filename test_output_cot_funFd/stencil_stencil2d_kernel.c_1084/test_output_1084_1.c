#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int s;
  int jj;
  int jj_col;
  int filter_elem;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      s = 0;
      inner:
      for (k = 0; k < 9; k++) {
        jj = j - 4 + k;
        if (((i < 8) || (jj < 8)) || (jj > 251)) {
          jj_col = i - 4 + k;
          if (((jj_col < 8) || (j < 8)) || (jj_col > 251)) {
            filter_elem = filter[k];
            s += orig[jj * 256 + jj_col] * filter_elem;
          }
        }
      }
      sol[i * 256 + j] = s;
    }
  }
}