5. #pragma ACCEL PIPELINE auto{off}: Disable pipelining for the loop.

6. #pragma ACCEL TILE FACTOR=auto{1}: Set the tiling factor to 1.

7. #pragma ACCEL PARALLEL FACTOR=auto{1}: Set the parallelization factor to 1.

8. #pragma ACCEL PARALLEL FACTOR=auto{16}: Set the parallelization factor to 16.

#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{494}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 32; j++) {
      out[i] += nzval[i * 32 + j] * vec[cols[i * 32 + j]];
    }
  }
}