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
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{2}
  loop:
/* Standardize from: for(i = 1; i < 32 + 1; i++) {...} */
  for (i = 1; i <= 32; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    inner1:
    for (j = 1; j <= 32; j++) {
      idx0 = (i - 1) * 32 + j - 1;
      idx = idx0;
      val = orig[idx0] * filter[0];
      idx1 = idx0 + 1;
      val += orig[idx1] * filter[1];
      idx2 = idx0 + 32;
      val += orig[idx2] * filter[2];
      idx3 = idx0 + 33;
      val += orig[idx3] * filter[3];
      idx4 = idx0 - 32;
      val += orig[idx4] * filter[4];
      idx5 = idx0 - 1;
      val += orig[idx5] * filter[5];
      idx6 = idx0 + 16;
      val += orig[idx6] * filter[6];
      idx7 = idx0 - 16;
      val += orig[idx7] * filter[7];
      idx8 = idx0 + 8;
      val += orig[idx8] * filter[8];
      sol[idx] = val;
    }
  }
}