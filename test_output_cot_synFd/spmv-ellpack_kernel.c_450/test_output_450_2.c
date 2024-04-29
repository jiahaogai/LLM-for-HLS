#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (j = 0; j < 494; j++) {
    double sum = ((double )0);
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
      int nz_i = cols[j + i * 16];
      
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{32}
      for (j = 0; j < 32; j++) {
        sum += nzval[nz_i + j * 494] * vec[j];
      }
    }
    out[i] = sum;
  }
}