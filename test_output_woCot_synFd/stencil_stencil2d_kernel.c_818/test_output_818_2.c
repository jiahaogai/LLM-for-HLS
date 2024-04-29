#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int buf[9];
  int total;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 8192; i++) {
    buf[0] = orig[i - 4];
    buf[1] = orig[i - 3];
    buf[2] = orig[i - 2];
    buf[3] = orig[i - 1];
    buf[4] = orig[i];
    buf[5] = orig[i + 1];
    buf[6] = orig[i + 2];
    buf[7] = orig[i + 3];
    buf[8] = orig[i + 4];
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    for (j = 0; j < 9; j++) {
      total = 0;
      
#pragma ACCEL PARALLEL reduction=total FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        total += filter[k] * buf[k];
      }
      sol[i - 4 + j] = total;
    }
  }
}