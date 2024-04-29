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
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    inner:
    for (j = 0; j < 256; j++) {
      idx0 = i * 256 + j;
      idx1 = idx0 + 256;
      idx2 = idx0 + 1;
      idx3 = idx1 + 1;
      idx4 = idx2 + 256;
      idx5 = idx3 + 256;
      idx6 = idx2 + 1;
      idx7 = idx3 + 1;
      idx8 = idx6 + 256;
      val = orig[idx0] + filter[0] * orig[idx1] + filter[1] * orig[idx2] + filter[2] * orig[idx3] + filter[3] * orig[idx4] + filter[4] * orig[idx5] + filter[5] * orig[idx6] + filter[6] * orig[idx7] + filter[7] * orig[idx8];
      sol[idx0] = val;
    }
  }
}