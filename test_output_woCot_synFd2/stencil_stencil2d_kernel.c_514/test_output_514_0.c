#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 8191; j++) {
      s = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        idx = (i + (-4 + k));
        if (idx < 0 || idx > 8191) {
          idx = ((idx < 0) ? 0 : 8191);
        }
        s += filter[k] * orig[idx * 8192 + j];
      }
      sol[i * 8192 + j] = s;
    }
  }
}