#pragma ACCEL PIPELINE auto{off}
#pragma ACCEL TILE FACTOR=auto{2}
#pragma ACCEL PARALLEL FACTOR=auto{16}

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = cols[i]; j < cols[i + 1]; j++) {
      out[i] += nzval[j] * vec[cols[j]];
    }
  }
}