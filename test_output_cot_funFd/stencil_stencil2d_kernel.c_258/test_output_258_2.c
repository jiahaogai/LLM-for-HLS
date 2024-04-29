#pragma ACCEL kernel

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
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8190; j++) {
      idx0 = i - 1;
      idx1 = i;
      idx2 = i + 1;
      idx3 = j - 1;
      idx4 = j;
      idx5 = j + 1;
      idx6 = idx4 * 8192 + 1;
      idx7 = idx4 * 8192 + 2;
      idx8 = idx4 * 8192 + 8190;
      val = filter[0] * orig[idx6 + idx0] + filter[1] * orig[idx6 + idx1] + filter[2] * orig[idx6 + idx2] + filter[3] * orig[idx7 + idx0] + filter[4] * orig[idx7 + idx1] + filter[5] * orig[idx7 + idx2] + filter[6] * orig[idx8 + idx0] + filter[7] * orig[idx8 + idx1] + filter[8] * orig[idx8 + idx2];
      sol[idx4 * 8192 + j] = val;
    }
  }
}