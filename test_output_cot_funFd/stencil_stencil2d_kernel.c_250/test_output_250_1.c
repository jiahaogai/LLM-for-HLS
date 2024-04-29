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
  int idy;
  int idz;
  int val;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      for (k = 0; k < 8; k++) {
        ti = 8 * i;
        tj = 8 * j;
        tk = 8 * k;
        val = ((orig[ti + tj + tk] * filter[0]) + (orig[ti + tj + tk + 1] * filter[1]) + (orig[ti + tj + tk + 8] * filter[2]) + (orig[ti + tj + tk + 9] * filter[3]) + (orig[ti + tj + tk + 16] * filter[4]) + (orig[ti + tj + tk + 17] * filter[5]) + (orig[ti + tj + tk + 24] * filter[6]) + (orig[ti + tj + tk + 25] * filter[7]) + (orig[ti + tj + tk + 32] * filter[8])) / 256;
        sol[ti + tj + tk] = val;
      }
    }
  }
}