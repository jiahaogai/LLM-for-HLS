#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  ellpack_1:
  for (j = 0; j < 48; j++) {
    ellpack_2:
    for (i = 0; i < 8; i++) {
      out[cols[j * 8 + i]] += nzval[j * 8 + i] * vec[j];
    }
  }
}