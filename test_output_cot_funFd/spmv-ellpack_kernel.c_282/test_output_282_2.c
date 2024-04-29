#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 14; j++) {
    i = 0;
    while (i < 494) {
      
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{2}
      out[cols[i + j * 14]] += nzval[i + j * 14] * vec[j];
      i += 16;
    }
  }
}