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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    for (j = 1; j < 8186; j++) {
      idx0 = i * 8192 + j;
      idx1 = idx0 - 8192;
      idx2 = idx1 - 1;
      idx3 = idx0 - 1;
      idx4 = idx0 + 1;
      idx5 = idx4 + 1;
      idx6 = idx3 - 8192;
      idx7 = idx4 - 8192;
      idx8 = idx7 - 1;
      sol[idx0] = filter[0] * orig[idx0] + filter[1] * (orig[idx1] + orig[idx2]) + filter[2] * (orig[idx3] + orig[idx4] + orig[idx5]) + filter[3] * (orig[idx6] + orig[idx7] + orig[idx8]);
    }
  }
}