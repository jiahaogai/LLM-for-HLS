#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[4940],double out[4940])
{
  int i;
  int j;
  for (i = 0; i < 4940; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 4940; i++) {
    out[cols[i]] += nzval[i] * vec[i];
  }
}