#pragma ACCEL kernel

void kernel(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        k_col = i + ((k % 3) - 1);
        int tmp_10;
        tmp_10 = k_col;
        assert(tmp_10 >= 0 && tmp_10 < 256);
        k_col = j + ((k / 3) - 1);
        int tmp_11;
        tmp_11 = k_col;
        assert(tmp_11 >= 0 && tmp_11 < 256);
        sum += ((orig[i * 256 + j]) * (filter[k])) * (orig[k_col]);
      }
      sol[i * 256 + j] = sum;
    }
  }
}