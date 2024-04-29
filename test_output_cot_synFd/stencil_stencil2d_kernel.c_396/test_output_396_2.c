#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int index;
  int flatten_index;
  int range_l;
  int range_r;
  int pad;
  pad = 1;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  loopj:
  for (j = 0; j < 64; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loopi:
    for (i = 0; i < 64; i++) {
      index = (((64 + (2 * pad)) * (j + pad)) + (i + pad)) ;
      flatten_index = ((index * 9)) ;
      range_l = (index - 9) ;
      range_r = (index + 9) ;
      loopk:
      for (k = range_l; k <= range_r; k++) {
        if ((((k < 0) || (k > 8191))) || ((k % 64) == 0)) {
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          sol[index] = 0;
        }
         else {
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          sol[index] += ((filter[((k % 9) + 1) - 1]) * orig[k]);
        }
      }
    }
  }
}