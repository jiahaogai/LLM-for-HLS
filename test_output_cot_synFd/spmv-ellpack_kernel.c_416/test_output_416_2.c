#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
  double sum;
  double nz;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (i = 0; i < 49; i++) {
    sum = ((double )0);
    for (j = 0; j < 10; j++) {
      nz = nzval[i * 10 + j];
      sum += nz * vec[cols[i * 10 + j]];
    }
    out[i] = sum;
  }
}