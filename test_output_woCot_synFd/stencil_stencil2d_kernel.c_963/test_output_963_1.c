#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int r;
  int c;
  int value;
  int temp[9];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      r = i - 4;
      c = j - 4;
      
#pragma ACCEL PARALLEL reduction=value FACTOR=auto{1}
      for (int _in_r = 0; _in_r < 9; _in_r++) {
        int _tmp_r = r + _in_r;
        temp[_in_r] = orig[_tmp_r * 8192 + c];
      }
      
#pragma ACCEL PARALLEL reduction=value FACTOR=auto{1}
      for (int _in_c = 0; _in_c < 9; _in_c++) {
        int _tmp_c = c + _in_c;
        value += filter[_in_c] * temp[_in_c];
      }
      sol[i * 8192 + j] = value;
      value = 0;
    }
  }
}