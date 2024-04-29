#pragma ACCEL kernel

void ellpack(double nzval[25],int cols[25],double vec[4],double out[1])
{
  int i;
  double sum;
  sum = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 25; i++) {
    sum += nzval[i] * vec[cols[i] - 1];
  }
  out[0] = sum;
}