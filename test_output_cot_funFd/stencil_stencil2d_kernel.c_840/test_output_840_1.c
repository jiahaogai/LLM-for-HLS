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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopi:
    for (i = 1; i < 33; i++) {
      idx0 = (j + 0) * 33 + (i + 0);
      idx1 = (j + 0) * 33 + (i + 1);
      idx2 = (j + 0) * 33 + (i + 2);
      idx3 = (j + 1) * 33 + (i + 0);
      idx4 = (j + 1) * 33 + (i + 1);
      idx5 = (j + 1) * 33 + (i + 2);
      idx6 = (j + 2) * 33 + (i + 0);
      idx7 = (j + 2) * 33 + (i + 1);
      idx8 = (j + 2) * 33 + (i + 2);
      val = filter[0] * orig[idx0] + filter[1] * orig[idx1] + filter[2] * orig[idx2] + filter[3] * orig[idx3] + filter[4] * orig[idx4] + filter[5] * orig[idx5] + filter[6] * orig[idx6] + filter[7] * orig[idx7] + filter[8] * orig[idx8];
      sol[idx0] = val;
    }
  }
}