Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 1; j++) {
      result = ((0 + filter[0]) * orig[i + 0]) + ((0 + filter[1]) * orig[i + 1]) + ((0 + filter[2]) * orig[i + 2]) + ((0 + filter[3]) * orig[i + 3]) + ((0 + filter[4]) * orig[i + 4]) + ((0 + filter[5]) * orig[i + 5]) + ((0 + filter[6]) * orig[i + 6]) + ((0 + filter[7]) * orig[i + 7]) + ((0 + filter[8]) * orig[i + 8]);
      sol[i] = result;
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 0; j < 1; j++) {
      result = ((0 + filter[0]) * orig[i + 0]) + ((0 + filter[1]) * orig[i + 1]) + ((0 + filter[2]) * orig[i + 2]) + ((0 + filter[3]) * orig[i + 3]) + ((0 + filter[4]) * orig[i + 4]) + ((0 + filter[5]) * orig[i + 5]) + ((0 + filter[6]) * orig[i + 6]) + ((0 + filter[7]) * orig[i + 7]) + ((0 + filter[8]) * orig[i + 8]);
      sol[i] = result;
    }
  }
}