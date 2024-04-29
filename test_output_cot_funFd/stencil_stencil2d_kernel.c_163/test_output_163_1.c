Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{126}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{flatten}
Code: #pragma ACCEL TILE FACTOR=auto{8}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{8}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{8}
Code: #pragma ACCEL PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{126}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
Code: #pragma ACCEL PIPELINE auto{off}
Code: #pragma ACCEL TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{8}
int filter[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
int orig[8192];
int sol[8192];
int stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      t = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{8}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (x = -1; x < 2; x++) {
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{8}
        for (y = -1; y < 2; y++) {
          t += filter[4 + x] * orig[i * 64 + (j * 8 + y) * 64 + x + 1];
        }
      }
      sol[i * 64 + j * 8 + 1] = t;
    }
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE