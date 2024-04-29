#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  double sum;
  double nz;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (i = 0; i < 494; i++) {
    sum = ((double )0);
    for (j = 0; j < 10; j++) {
      nz = nzval[i * 10 + j];
      vec[j] = nz;
      sum += nz * vec[j];
    }
    out[i] = sum;
  }
}