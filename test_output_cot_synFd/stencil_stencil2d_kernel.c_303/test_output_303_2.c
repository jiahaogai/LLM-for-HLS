#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 8192; j++) {
      result = 0;
      inner:
      for (k = 0; k < 9; k++) {
        int cur_filter = filter[k];
        int cur_index = i + ((k - 4) << 11);
        // The following condition would throw an Array Index Out Of Bounds
        // Exception. But it will not be reached in this example since the
        // filters have been constructed such that they do not overflow the
        // borders.
        if (((cur_index) < 8192) && ((cur_index) >= 0)) 
          result += cur_filter * orig[cur_index];
      }
      sol[j] = result;
    }
  }
}