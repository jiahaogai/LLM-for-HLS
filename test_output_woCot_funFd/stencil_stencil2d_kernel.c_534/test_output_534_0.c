#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int k_col;
  int buff[9];
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k = 0, k_col = 0; k < 9; k++, k_col++) {
        buff[k] = orig[i + (k_col - 4) + ((j + (k_col - 4)) * 256)];
      }
      sol[i * 256 + j] = ((buff[0] + buff[1] + buff[2]) + (buff[3] + buff[4] + buff[5]) + (buff[6] + buff[7] + buff[8])) - (filter[0] + filter[1] + filter[2]) * ((buff[0] + buff[1] + buff[2]) + (buff[6] + buff[7] + buff[8]));
    }
  }
}