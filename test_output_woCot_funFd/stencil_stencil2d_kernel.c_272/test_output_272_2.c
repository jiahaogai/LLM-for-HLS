#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int i;
  int j;
  int k;
  int idx;
  int idy;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{126}
  outer:
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 400 - 1; j++) {
      idx = -25 + 1;
      
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{1}
      inner:
      while (idx < 25 - 1) {
        idy = -25 + 1;
        
#pragma ACCEL PARALLEL reduction=result FACTOR=auto{16}
        inner_1:
        while (idy < 25 - 1) {
          result += ((int )orig[i + idx][j + idy]) * filter[idx + 25 - 1];
          idy += 1;
        }
        idx += 1;
      }
      sol[i][j] = result;
      result = 0;
    }
  }
}