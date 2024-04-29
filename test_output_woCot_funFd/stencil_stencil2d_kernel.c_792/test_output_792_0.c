#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  int index;
  int bottom;
  int top;
  int left;
  int right;
  bottom = 256 * 2 - 1;
  top = 256 * 0;
  left = 256 - 1;
  right = 256 * 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = top; j < bottom; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = left; i < right; i++) {
      index = i + j * 256;
      result = ((orig[index - 2] + orig[index - 1] + orig[index]) + (orig[index + 1] + orig[index + 2])) / 8;
      sol[index] = result;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = top; j < bottom; j++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = left; i < right; i++) {
      index = i + j * 256;
      result = ((sol[index - 2] + sol[index - 1] + sol[index]) + (sol[index + 1] + sol[index + 2])) / 8;
      if (result < 0) {
        result = 0;
      }
      if (result > 255) {
        result = 255;
      }
      sol[index] = result;
    }
  }
}