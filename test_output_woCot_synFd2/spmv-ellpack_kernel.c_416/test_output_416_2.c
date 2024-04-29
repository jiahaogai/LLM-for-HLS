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
    for (j = cols[i]; j < cols[i + 1]; j++) {
      nz = nzval[j];
      sum += nz * vec[cols[j]];
    }
    out[i] = sum;
  }
}