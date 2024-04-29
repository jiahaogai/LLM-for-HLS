Code: ### Body:
 
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      midx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      filter:
      for (k = -4; k <= 4; k++) {
        int cur = orig[idx + k];
        sum += cur * filter[midx];
        midx++;
      }
      sol[idx] = sum;
      idx++;
    }
  }
}
Error: 
Please check the code and try again.
Code: ### Body:
 
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      midx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      filter:
      for (k = -4; k <= 4; k++) {
        int cur = orig[idx + k];
        sum += cur * filter[midx];
        midx++;
      }
      sol[idx] = sum;
      idx++;
    }
  }
}
Error: 
Please check the code and try again.
Code: ### Body:
 
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int sum;
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{9}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner:
    for (j = 0; j < 256; j++) {
      sum = 0.0;
      midx = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      filter:
      for (k = -4; k <= 4; k++) {
        int cur = orig[idx + k];
        sum += cur * filter[midx];
        midx++;
      }