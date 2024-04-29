#pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 0; j < 44; j++) {
    i = 0 + cols[j];
    out[i] += nzval[j] * vec[j];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 44; j < 88; j++) {
    i = 32 + cols[j];
    out[i] += nzval[j] * vec[j];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 88; j < 132; j++) {
    i = 64 + cols[j];
    out[i] += nzval[j] * vec[j];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 132; j < 176; j++) {
    i = 96 + cols[j];
    out[i] += nzval[j] * vec[j];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 176; j < 220; j++) {
    i = 128 + cols[j];
    out[i] += nzval[j] * vec[j];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 220; j < 264; j++) {
    i = 160 + cols[j];
    out[i] += nzval[j] * vec[j];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 264; j < 308; j++) {
    i = 192 + cols[j];
    out[i] += nzval[j] * vec[j];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 308; j < 352; j++) {
    i = 224 + cols[j];
    out[i] += nzval[j] * vec[j];
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{19}
  for (j = 35