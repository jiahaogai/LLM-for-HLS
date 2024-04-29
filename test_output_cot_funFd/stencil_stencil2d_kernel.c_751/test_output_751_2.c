#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int ti;
  int tj;
  int tk;
  int hw = 4;
  int hw2 = 2 + 4 - 1;
  int pad = 4;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 0; j < 8; j++) {
      inner:
      for (k = 0; k < 8; k++) {
        ti = pad + i * hw;
        tj = pad + j * hw;
        tk = pad + k * hw;
        sol[ti + tj + tk] = 0;
        inner_1:
        for (k = 0; k < 9; k++) {
          sol[ti + tj + tk] += filter[k] * orig[ti + tj + tk + (k - 4)];
        }
      }
    }
  }
}