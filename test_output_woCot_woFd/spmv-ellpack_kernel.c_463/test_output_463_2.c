5. `#pragma ACCEL PARAM nzval[]`: Pass the `nzval` array to the hardware accelerator.
6. `#pragma ACCEL PARAM cols[]`: Pass the `cols` array to the hardware accelerator.
7. `#pragma ACCEL PARAM vec[]`: Pass the `vec` array to the hardware accelerator.
8. `#pragma ACCEL PARAM out[]`: Pass the `out` array to the hardware accelerator.

#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 64; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{4}
    for (i = 0; i < 64; i++) {
      out[cols[j + (i << 6)]] += nzval[j + (i << 6)] * vec[i];
    }
  }
}