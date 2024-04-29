#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int s;
  int jj;
  int jj_col;
  int result;
  
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
      for (k = -4; k < 5; k++) {
        jj = j + k;
        if (((jj >= 0) && (jj < 256))) {
          jj_col = i + k;
          if (((jj_col >= 0) && (jj_col < 256))) {
            s += ((orig[jj * 256 + jj_col] * filter[k + 4]) - 32768);
          }
        }
      }
      result = s / 256;
      if (result < 0) {
        result = 0;
      }
       else if (result > 65535) {
        result = 65535;
      }
       sol[j * 256 + i] = result;
    }
  }
}