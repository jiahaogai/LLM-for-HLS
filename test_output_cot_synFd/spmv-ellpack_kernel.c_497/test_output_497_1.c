#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{8}
void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (j = 0; j < 50; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{8}
    for (i = 0; i < 494; i++) {
      out[i] += nzval[cols[j] + i * 50] * vec[j];
    }
  }
}