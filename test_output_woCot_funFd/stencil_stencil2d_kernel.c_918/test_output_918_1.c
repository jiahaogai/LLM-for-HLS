#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
      inner:
      for (k = 0; k < 9; k++) {
        int cur_filter;
        int cur_array;
        cur_filter = filter[k];
        cur_array = orig[i + ((k - 4) << 8) + ((-4) << 8)];
        sum += cur_filter * cur_array;
      }
      sol[i + j << 8] = sum;
    }
  }
}