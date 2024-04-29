Code: #pragma ACCEL PIPELINE auto{flatten}
   - Translation: PIPELINE auto{flatten}
   - Explanation: PIPELINE auto{flatten}
Code: #pragma ACCEL TILE FACTOR=auto{8}
   - Translation: TILE FACTOR=auto{8}
   - Explanation: TILE FACTOR=auto{8}
Code: #pragma ACCEL PARALLEL FACTOR=auto{8}
   - Translation: PARALLEL FACTOR=auto{8}
   - Explanation: PARALLEL FACTOR=auto{8}
Code: #pragma ACCEL PIPELINE auto{}
   - Translation: PIPELINE auto{}
   - Explanation: PIPELINE auto{}
Code: #pragma ACCEL TILE FACTOR=auto{1}
   - Translation: TILE FACTOR=auto{1}
   - Explanation: TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{8}
   - Translation: PARALLEL FACTOR=auto{8}
   - Explanation: PARALLEL FACTOR=auto{8}
Code: #pragma ACCEL PIPELINE auto{flatten}
   - Translation: PIPELINE auto{flatten}
   - Explanation: PIPELINE auto{flatten}
Code: #pragma ACCEL TILE FACTOR=auto{1}
   - Translation: TILE FACTOR=auto{1}
   - Explanation: TILE FACTOR=auto{1}
Code: #pragma ACCEL PARALLEL FACTOR=auto{1}
   - Translation: PARALLEL FACTOR=auto{1}
   - Explanation: PARALLEL FACTOR=auto{1}
 */
 #pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loopj:
  for (j = 8; j < 8184 + 8; j++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    loopk:
    for (k = 8; k < 8192 + 8; k++) {
      idx = (j + 8192) * 8192 + k + 8;
      val = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 0; i < 9; i++) {
        val += filter[i] * orig[(j + i - 8) * 8192 + k - 8];
      }
      sol[idx] = val;
    }
  }
}