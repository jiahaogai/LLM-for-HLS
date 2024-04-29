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
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  outer:
  for (i = 0; i < 8192; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    middle:
    for (j = 0; j < 64; j++) {
      idx0 = i - 1;
      idx1 = i + 1;
      idx2 = ((j - 1) << 12) + i - 1;
      idx3 = ((j + 1) << 12) + i - 1;
      idx4 = ((j - 1) << 12) + i;
      idx5 = ((j + 1) << 12) + i;
      idx6 = ((j - 1) << 12) + i + 1;
      idx7 = ((j + 1) << 12) + i + 1;
      idx8 = ((j << 12)) + i;
      
#pragma ACCEL PARALLEL reduction=orig FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        if (k == 4) {
          val = orig[idx8];
        }
        
#pragma ACCEL PIPELINE auto{off}
        
#pragma ACCEL TILE FACTOR=auto{1}
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        else {
          val = ((0 <= idx0 ? filter[k] * orig[idx0--] : 0) + (0 <= idx1 ? filter[k] * orig[idx1++] : 0) + (0 <= idx2 ? filter[k] * orig[idx2--] : 0) + (0 <= idx3 ? filter[k] * orig[idx3++] : 0) + (0 <= idx4 ? filter[k] * orig[idx4] : 0) + (0 <= idx5 ? filter[k] * orig[idx5] : 0) + (0 <= idx6 ? filter[k] * orig[idx6++] : 0) + (0 <= idx7 ? filter[k] * orig[idx7++] : 0) + (0 <= idx8 ? filter[k] * orig[idx8] : 0));
        }
        sol[idx8] = val;
        idx8 += 8192;
      }
    }
  }
}