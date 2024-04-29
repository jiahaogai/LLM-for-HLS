#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int idxm2;
  int idxm1;
  int idxp1;
  int idxp2;
  int idym2;
  int idym1;
  int idyp1;
  int idyp2;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
  for (j = 1; j < 33; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loopi:
    for (i = 1; i < 33; i++) {
      idx = i + 32 * j;
      val = orig[idx];
      idym2 = idx - 64;
      idym1 = idx - 32;
      idyp1 = idx + 32;
      idyp2 = idx + 64;
      loopk:
      for (k = 0; k < 9; k++) {
        idxm2 = idym2 + k - 4;
        idxm1 = idym1 + k - 4;
        idxp1 = idyp1 + k - 4;
        idxp2 = idyp2 + k - 4;
        val += filter[k] * orig[idxm2] + orig[idxm1] + orig[idxp1] + orig[idxp2];
      }
      sol[idx] = val;
    }
  }
}