#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[2][2])
{
  int i;
  int j;
  int fl;
  int il;
  int jl;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  outer:
  for (i = 1; i < 3; i++) {
    
#pragma ACCEL PIPELINE auto{fl=2}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    middle:
    for (j = 1; j < 3; j++) {
      sol[i][j] = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      inner:
      for (fl = 0; fl < 2; fl++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        inner_1:
        for (il = -1; il <= 1; il++) {
          
#pragma ACCEL PARALLEL FACTOR=auto{1}
          inner_2:
          for (jl = -1; jl <= 1; jl++) {
            sol[i][j] += filter[fl][0] * orig[i + il][j + jl];
          }
        }
      }
    }
  }
}