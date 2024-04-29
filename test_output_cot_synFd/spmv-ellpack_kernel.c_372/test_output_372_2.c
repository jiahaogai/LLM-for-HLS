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
  for (j = 0; j < 4; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{1}
    for (i = 0; i < 121; i++) {
      out[cols[j * 121 + i]] += nzval[j * 121 + i] * vec[j * 121 + i];
    }
  }
}