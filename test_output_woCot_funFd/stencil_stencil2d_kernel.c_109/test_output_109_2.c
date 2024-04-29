#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{8}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int tmpp;
  int range = 32 + 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 32; i < 8168 + 32; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 32; j < 8168 + 32; j++) {
      tmp = 0;
      inner:
      for (k = -32; k < -1 + 32; k++) {
        tmpp = k + j;
        if (tmpp >= 32 && tmpp < 8168 + 32) {
          tmp += ((orig[tmpp]) * (filter[k + 32])) ;
        }
      }
      sol[i * (8192) + j] = tmp;
    }
  }
}