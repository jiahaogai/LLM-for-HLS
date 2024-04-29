#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt[9];
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{8}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 9; k++) {
        pt[k] = filter[k];
      }
      
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{8}
      inner_1:
      for (k = 1; k < 9; k++) {
        t = i * 8 + j * 1 + k - 4;
        pt[k] = orig[t] * pt[k];
      }
      sol[i * 8 + j] = pt[4] + ((pt[5] + pt[6]) + (pt[7] + pt[8]));
    }
  }
}