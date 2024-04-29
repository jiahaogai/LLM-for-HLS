#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int center = 45;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{7}
  outer:
  for (i = 1; i < 8190; i++) {
    
#pragma ACCEL PIPELINE auto{flatten}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    middle:
    for (j = 1; j < 8176; j++) {
      idx = (i - 1) * 8176 + j - 1;
      sol[idx] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (k = 0; k < 9; k++) {
        int offset = k - center;
        int x = i + offset;
        int y = j + offset;
        if (x < 1 || x > 8190) {
          x = 1;
        }
        
        if (y < 1 || y > 8176) {
          y = 1;
        }
        
        sol[idx] += filter[k] * orig[x * 8176 + y];
      }
    }
  }
}