#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int idx;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      idx = i * 8192 + j;
      val = orig[idx];
      tk = ((-filter[0] / 2) + 8) + filter[0];
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{2}
      for (k = (-filter[0] / 2) + 1; k < tk; k++) {
        tj = j + k;
        if (tj < 1) {
          tj = 1;
        }
        else {
          if (tj > 8192) {
            tj = 8192;
          }
        }
        sol[idx] += val * filter[k + (-filter[0] / 2)];
      }
    }
  }
}