Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (x = -1; x <= 1; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_1:
        for (y = -1; y <= 1; y++) {
          t += filter[(((x * 2) + 1) * 3) + ((y * 2) + 1)] * orig[i + x][j + y];
        }
      }
      sol[i][j] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:35:73: error: subscripted value is neither array nor pointer nor vector
   35 |           t += filter[(((x * 2) + 1) * 3) + ((y * 2) + 1)] * orig[i + x][j + y];
      |                                                                         ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:38:13: error: subscripted value is neither array nor pointer nor vector
   38 |       sol[i][j] = t;
      |             ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8191; j++) {
      t = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (x = -1; x <= 1; x++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_1:
        for (y = -1; y <= 1; y++) {
          t += filter[(((x * 2) + 1) * 3) + ((y * 2) + 1)] * orig[i + x][j + y];
        }
      }
      sol[i][j] = t;
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil’:
/root/autodl-tmp/