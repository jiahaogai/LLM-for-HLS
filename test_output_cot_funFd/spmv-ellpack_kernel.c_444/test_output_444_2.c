#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{4}
#pragma ACCEL PARALLEL FACTOR=auto{2}

void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 49; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
  }
}