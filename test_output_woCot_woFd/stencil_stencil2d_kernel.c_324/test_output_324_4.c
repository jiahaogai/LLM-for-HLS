#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int r;
  int c;
  int value;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  for (r = 0; r < 128 + 2; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (c = 0; c < 64 + 2; c++) {
      value = ((r - 1) * (64 + 2) + c - 1) * 2;
      sol[value] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{9}
      for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
          sol[value] += filter[i * 9 + j] * orig[value + i * (64 + 2) + j];
        }
      }
    }
  }
}