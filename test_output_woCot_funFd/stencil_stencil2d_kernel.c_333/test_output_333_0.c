#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int row;
  int col;
  int flatten_filter[81];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 81; i++) {
    flatten_filter[i] = filter[i];
  }
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{32}
  for (i = 1; i < 8; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8; j++) {
      row = i - 1 + -40;
      col = j - 1 + -40;
      k = 0;
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{1}
      while (k < 9) {
        sol[row * 8 + col] += flatten_filter[k] * orig[row * 8 + col + k - 4];
        k++;
      }
    }
  }
}