#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
  }
}