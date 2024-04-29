#pragma ACCEL kernel

void kernel_stencil(int orig[8192],int sol[8192],int filter[9])
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
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{4}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 256; j++) {
      idx0 = i * 256 + j;
      idx1 = idx0 - 256;
      idx2 = idx1 - 1;
      idx3 = idx0 - 1;
      idx4 = idx0 + 1;
      idx5 = idx4 + 256;
      idx6 = idx3 - 2;
      idx7 = idx4 - 2;
      idx8 = idx5 - 2;
      val = orig[idx0] + filter[0] * orig[idx1] + filter[1] * orig[idx2] + filter[2] * orig[idx3] + filter[3] * orig[idx4] + filter[4] * orig[idx5] + filter[5] * orig[idx6] + filter[6] * orig[idx7] + filter[7] * orig[idx8];
      sol[idx0] = val;
    }
  }
}