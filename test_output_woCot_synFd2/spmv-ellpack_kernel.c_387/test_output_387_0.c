#pragma ACCEL kernel

void ellpack(double nzval[120],int cols[120],double vec[24],double out[16])
{
  int i;
  int j;
  double sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 16; i++) {
    sum = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 0; j < 4; j++) {
      sum += nzval[i * 4 + j] * vec[cols[i * 4 + j]];
    }
    out[i] = sum;
  }
}