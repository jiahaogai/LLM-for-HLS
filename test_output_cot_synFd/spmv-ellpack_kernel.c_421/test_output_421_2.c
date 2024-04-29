#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{13}
  for (j = 0; j < 49; j++) {
    for (i = 0; i < 32; i++) {
      out[cols[j * 32 + i]] += nzval[j * 32 + i] * vec[j];
    }
  }
}