The ACCEL compiler will automatically optimize and parallelize in an optimal way. The user does not have to be concerned about this type of optimization in his/her application code.

#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int t;
  int pt = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{6}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{64}
    inner:
    for (j = 0; j < 9; j++) {
      k = i - 4 + j;
      if (k < 0 || k > 8191) {
        t += filter[j] * 0;
      }
      
#pragma ACCEL PARALLEL reduction=t FACTOR=auto{16}
      else {
        t += filter[j] * orig[k];
      }
    }
    sol[i] = t;
  }
}