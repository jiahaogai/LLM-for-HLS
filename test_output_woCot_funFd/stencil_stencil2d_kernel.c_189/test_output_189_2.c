#pragma ACCEL kernel

void stencil(int orig[25],int sol[25],int filter[25])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PARALLEL reduction = orig FACTOR=auto{25}
    for (j = 0; j < 25; j++) {
      sol[i] = ((orig[i - 1] + orig[i + 1]) + (orig[j - 1] + orig[j + 1])) + filter[j];
    }
  }
}