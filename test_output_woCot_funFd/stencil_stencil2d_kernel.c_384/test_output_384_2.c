#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int tmp;
  int t;
  int pt = 4 * 8192;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 8; i < 8184; i += 8) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    middle:
    for (j = 8; j < 8184; j += 8) {
      tmp = 0;
      
#pragma ACCEL PARALLEL reduction = tmp FACTOR=auto{32}
      inner:
      for (k = -4; k < 5; k++) {
        t = i + k;
        if (((t < 0) || (8192 < t))) {
          tmp += filter[4 + k];
        }
         else {
          tmp += orig[t] * filter[4 + k];
        }
      }
      sol[pt] = tmp;
      pt++;
    }
  }
}