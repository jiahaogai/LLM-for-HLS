#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf[9];
  int index;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 256; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        buf[k] = orig[((i + (-4 + k))) * 256 + j];
      }
      sol[i * 256 + j] = ((buf[0] + buf[1] + buf[2]) + (buf[3] + buf[4] + buf[5]) + (buf[6] + buf[7] + buf[8])) - (((buf[0] + buf[1] + buf[2]) + (buf[6] + buf[7] + buf[8])) + ((buf[3] + buf[4] + buf[5]) + (buf[6] + buf[7] + buf[8])));
    }
  }
}