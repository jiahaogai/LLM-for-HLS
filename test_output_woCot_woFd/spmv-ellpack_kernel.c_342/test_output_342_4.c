#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 40; j++) {
      out[i] += nzval[cols[i + j * 494] - 1] * vec[j];
    }
  }
}