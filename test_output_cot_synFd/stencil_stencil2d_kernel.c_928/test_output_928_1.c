#pragma ACCEL kernel

void stencil(int orig[25],int sol[25],int filter[25])
{
  int i;
  int j;
  int jj;
  int ii;
  int x;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{21}
  outer:
  for (i = 0; i < 25; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 0; j < 25; j++) {
      x = 0;
      
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
      inner:
      for (jj = -1; jj <= 1; jj++) {
        
#pragma ACCEL PARALLEL reduction=x FACTOR=auto{1}
        inner_1:
        for (ii = -1; ii <= 1; ii++) {
          if ((((i + ii) >= 0) && ((i + ii) < 25)) && (((j + jj) >= 0) && ((j + jj) < 25))) {
            x += filter[25 * jj + ii] * orig[25 * (i + ii) + (j + jj)];
          }
        }
      }
      sol[i * 25 + j] = x;
    }
  }
}