#pragma ACCEL kernel

void ellpack(double nzval[15],int cols[15],double vec[3],double out[1])
{
  int i;
  int j;
  double sum;
  sum = ((double )0);
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 15; i++) {
    sum += nzval[i] * vec[cols[i]];
  }
  out[0] = sum;
}