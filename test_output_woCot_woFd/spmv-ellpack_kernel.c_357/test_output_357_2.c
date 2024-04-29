5. #pragma ACCEL PARAMETER FACTOR=auto{494}:
   Indicate that the parameter 'nzval' has a scale factor of 494.

6. #pragma ACCEL PARAMETER FACTOR=auto{4940}:
   Indicate that the parameter 'cols' has a scale factor of 4940.

7. #pragma ACCEL PARAMETER FACTOR=auto{494}:
   Indicate that the parameter 'vec' has a scale factor of 494.

8. #pragma ACCEL PARAMETER FACTOR=auto{494}:
   Indicate that the parameter 'out' has a scale factor of 494.

#pragma ACCEL kernel

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{4}

#pragma ACCEL PARALLEL FACTOR=auto{16}
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 494; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (j = 0; j < 16; j++) {
      out[i] += nzval[(i * 16 + j)] * vec[cols[(i * 16 + j)]];
    }
  }
}