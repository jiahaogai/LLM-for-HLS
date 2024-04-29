#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  for (i = 0; i < 494; i++) {
    for (j = 0; j < 32; j++) {
      out[cols[i + (j << 8)]] += nzval[i + (j << 8)] * vec[i];
    }
  }
}