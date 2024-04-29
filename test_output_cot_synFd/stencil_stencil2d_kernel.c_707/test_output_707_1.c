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
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k_col = 0; k_col < 9; k_col++) {
        k = i - 4 + k_col;
        buff[k_col] = ((k < 0) ? orig[i * 256 + j] : ((k > 255) ? orig[i * 256 + j] : orig[k * 256 + j]));
      }
      sol[i * 256 + j] = ((filter[0] * buff[0]) + (filter[1] * buff[1]) + (filter[2] * buff[2]) + (filter[3] * buff[3]) + (filter[4] * buff[4]) + (filter[5] * buff[5]) + (filter[6] * buff[6]) + (filter[7] * buff[7]) + (filter[8] * buff[8])) >> 12;
    }
  }
}