#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{1}
    for (j = 0; j < 10; j++) {
      out[i] += nzval[i * 10 + j] * vec[cols[i * 10 + j]];
    }
  }
}