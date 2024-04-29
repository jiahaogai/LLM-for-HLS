#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int index;
  double sum;
  int nz;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop:
  for (index = 0; index < 494; index++) {
    sum = ((double )0);
    nz = cols[index];
    data:
    while (nz < cols[index + 1]) {
      j = nzval[nz] - 1;
      sum += nzval[nz] * vec[j];
      nz++;
    }
    out[index] = sum;
  }
}