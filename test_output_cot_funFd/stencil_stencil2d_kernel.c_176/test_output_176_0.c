#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int flatten_i;
  int flatten_j;
  int idx = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop:for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner1:for (j = 0; j < 256; j++) {
      flatten_i = i * 256;
      flatten_j = j * 16;
      int sum = 0.0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner2:for (k = 0; k < 9; k++) {
        int cur = filter[k] * orig[flatten_i + (flatten_j + k)];
        sum = sum + cur;
      }
      sol[idx] = sum;
      idx++;
    }
  }
}