#pragma ACCEL PIPELINE auto{}
#pragma ACCEL TILE FACTOR=auto{1}
#pragma ACCEL PARALLEL FACTOR=auto{7}

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  loopj:
/* Standardize from: for(j ... */
  for (j = 1; j < 64 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
/* Standardize from: for(i ... */
    for (i = 1; i < 128 - 1; i++) {
      idx0 = i - 1 + ((j - 1) * 128);
      idx1 = i + ((j - 1) * 128);
      idx2 = i + 1 + ((j - 1) * 128);
      idx3 = i - 1 + (j * 128);
      idx4 = i + (j * 128);
      idx5 = i + 1 + (j * 128);
      idx6 = i - 1 + (j + 1) * 128;
      idx7 = i + (j + 1) * 128;
      idx8 = i + 1 + (j + 1) * 128;
      val = filter[0] * orig[idx0] + filter[1] * orig[idx1] + filter[2] * orig[idx2] + filter[3] * orig[idx3] + filter[4] * orig[idx4] + filter[5] * orig[idx5] + filter[6] * orig[idx6] + filter[7] * orig[idx7] + filter[8] * orig[idx8];
      sol[idx4] = val;
    }
  }
}