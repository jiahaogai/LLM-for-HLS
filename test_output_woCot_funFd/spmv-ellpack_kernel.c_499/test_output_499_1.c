Code: #pragma ACCEL PIPELINE auto{off}`: Do not automatically pipeline this loop.
- `#pragma ACCEL TILE FACTOR=auto{1}`: Do not divide this loop into smaller parts.
- `#pragma ACCEL PARALLEL FACTOR=auto{1}`: Execute loop iterations concurrently, setting the parallelization factor to 1.
- `#pragma ACCEL PARAMS FAST MEM`: Specify that this function uses the FAST memory space.

#pragma ACCEL kernel

void kernel_1(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  spmv_1:
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    spmv_2:
    for (j = 0; j < 32; j++) {
      sum += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
    }
    out[i] = sum;
  }
}