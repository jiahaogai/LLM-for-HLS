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
  
#pragma ACCEL TILE FACTOR=auto{8}
  
#pragma ACCEL PARALLEL FACTOR=auto{14}
  outer:
  for (i = 0; i < 8192; i++) {
    val = orig[i] * filter[4];
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    inner:
    for (j = 1; j <= 4; j++) {
      idx0 = i - 1 - 1 * j;
      idx1 = i - 1 + 0 * j;
      idx2 = i - 1 + 1 * j;
      idx3 = i + 0 - 1 * j;
      idx4 = i + 0 + 0 * j;
      idx5 = i + 0 + 1 * j;
      idx6 = i + 1 - 1 * j;
      idx7 = i + 1 + 0 * j;
      idx8 = i + 1 + 1 * j;
      val += orig[idx0] * filter[0 + 4 * j];
      val += orig[idx1] * filter[1 + 4 * j];
      val += orig[idx2] * filter[2 + 4 * j];
      val += orig[idx3] * filter[3 + 4 * j];
      val += orig[idx4] * filter[4 + 4 * j];
      val += orig[idx5] * filter[5 + 4 * j];
      val += orig[idx6] * filter[6 + 4 * j];
      val += orig[idx7] * filter[7 + 4 * j];
      val += orig[idx8] * filter[8 + 4 * j];
    }
    sol[i] = val;
  }
}