#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int r;
  int c;
  int i;
  int j;
  int k;
  int flatten_filter[81];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (r = 1; r < 8191; r++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (c = 1; c < 8191; c++) {
      i = 0;
      
#pragma ACCEL PIPELINE auto{off}
      while (i < 8) {
        j = 0;
        
#pragma ACCEL PIPELINE auto{off}
        while (j < 8) {
          k = r - 4 + i;
          int _in_val = ((k >= 0 && k < 8192) ? orig[k] : 0);
          flatten_filter[j] = _in_val;
          j++;
        }
        int _flatten_sum = 0;
        int _flatten_idx = 0;
        
#pragma ACCEL PARALLEL reduction=_flatten_sum FACTOR=auto{1}
        while (_flatten_idx < 8) {
          _flatten_sum += flatten_filter[_flatten_idx] * filter[i * 8 + _flatten_idx];
          _flatten_idx++;
        }
        sol[r * 8192 + c] = _flatten_sum;
        i++;
      }
    }
  }
}