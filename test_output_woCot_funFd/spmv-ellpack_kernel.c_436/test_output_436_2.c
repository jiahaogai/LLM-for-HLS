#pragma ACCEL PIPELINE auto{}: Automatically pipeline the loop to optimize for parallel execution.

#pragma ACCEL TILE FACTOR=auto{1}: Keep the loop whole without dividing it into smaller parts, and let the tool decide the optimized factor for tiling.

#pragma ACCEL PARALLEL FACTOR=auto{2}: Execute loop iterations concurrently with a factor of 2, allowing parallel processing to optimize performance.

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
      sum += nzval[(i * 16 + j)] * vec[cols[(i * 16 + j)]];
    }
    out[i] = sum;
  }
}