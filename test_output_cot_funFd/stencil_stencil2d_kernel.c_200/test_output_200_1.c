Code: #pragma ACCEL PIPELINE auto{}`:
  - Automatically pipeline the loop for better performance.

- `#pragma ACCEL TILE FACTOR=auto{1}`:
  - Automatically divide the loop into tiles of 1 elements for parallel processing.

- `#pragma ACCEL PARALLEL FACTOR=auto{1}`:
  - Automatically parallelize the loop.

- `#pragma ACCEL PARALLEL FACTOR=auto{16}`:
  - Shift the FACTOR down to 16.

- `#pragma ACCEL PIPELINE auto{off}`:
  - Turn off pipelining for the loop.

- `#pragma ACCEL TILE FACTOR=auto{2}`:
  - Automatically divide the loop into tiles of 2 elements for parallel processing.

- `#pragma ACCEL PARALLEL FACTOR=auto{1}`:
  - Execute loop iterations sequentially, not concurrently.

- `#pragma ACCEL PARALLEL FACTOR=auto{1}`:
  - Automatically parallelize the loop.


#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{16}
      inner:
      for (k = -4; k < 5; k++) {
        idx = (256 + (i + k)) % 256;
        val += filter[4 + k] * orig[256 * idx + j];
      }
      sol[256 * i + j] = val;
    }
  }
}