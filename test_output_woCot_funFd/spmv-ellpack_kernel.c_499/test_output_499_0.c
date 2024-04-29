#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (j = 0; j < 5; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (i = 0; i < 494; i++) {
      out[i] += nzval[cols[i] + 5L * j] * vec[j];
    }
  }
}