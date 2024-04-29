#pragma ACCEL kernel

void ellpack(double nzval[32],int cols[32],double vec[2],double out[1])
{
  int i;
  int j;
  double sum;
  sum = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 4; i++) {
    sum += nzval[i] * vec[cols[i]];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  out[0] = sum;
}