#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tmp;
  int t;
  ti = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{8}
  while (ti < 8) {
    tj = 0;
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    while (tj < 8) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction=tmp FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        t = k + ((8 * ti) + tj) * 9;
        tmp += filter[k] * orig[t];
      }
      sol[tj + ti * 8] = tmp;
      tj++;
    }
    ti++;
  }
}