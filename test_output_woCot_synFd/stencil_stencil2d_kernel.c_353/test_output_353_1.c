#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    tmp = 0;
    
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{16}
    inner:
    for (k = 0; k < 9; k++) {
      tmp += orig[i + (-4 + k)] * filter[k];
    }
    
#pragma ACCEL PARALLEL reduction=sol FACTOR=auto{16}
    sol[i] = tmp;
  }
}