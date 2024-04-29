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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 256; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 256; j++) {
      idx0 = i * 256 + j;
      idx = idx0;
      val = orig[idx0];
      idx1 = idx0 + 1;
      val += filter[0] * orig[idx1];
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
      inner:
      for (k = 1; k < 9; k++) {
        idx = idx1;
        idx1 += 1;
        val += filter[k] * orig[idx1];
      }
      sol[idx0] = val;
    }
  }
}