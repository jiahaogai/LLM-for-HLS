#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (i = 0; i < 494; i++) {
    out[i] = 0.0;
    
#pragma ACCEL PARALLEL FACTOR=auto{19}
    for (j = 0; j < 16; j++) {
      out[i] += nzval[i * 16 + j] * vec[cols[i * 16 + j]];
    }
  }
}