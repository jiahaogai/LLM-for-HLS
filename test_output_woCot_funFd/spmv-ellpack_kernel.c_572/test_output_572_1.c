#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int index;
  int n;
  double sum;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  loop:
  for (n = 0; n < 494; n++) {
    sum = ((double )0);
    indx:
    for (index = cols[n]; index < cols[n + 1]; index++) {
      sum += nzval[index] * vec[cols[index]];
    }
    out[n] = sum;
  }
}