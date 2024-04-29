Code: #pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{8}`: Divide this loop into 8 smaller loops, which are kept whole.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PIPELINE auto{flatten}`: Flatten the loops in this loop pipeline.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{8}`: OpenMP parallelize this loop, with a factor of 8.
- `#pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Keep this loop whole, without dividing it into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations sequentially, not concurrently.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: OpenMP parallelize this loop.

#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
  }
}
Error: 
Please check the code and try again.
Code: #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{1}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
  }
}