#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{2}
void ellpack(double nzval[4940],int cols[4940],double vec[49],double out[49])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  for (i = 0; i < 49; i++) {
    out[i] = ((double )0);
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    for (j = 0; j < 50; j++) {
      out[i] += nzval[i * 50 + j] * vec[cols[i * 50 + j]];
    }
  }
}