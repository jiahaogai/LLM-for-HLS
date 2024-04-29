#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int t;
  int x;
  int y;
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{126}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8192; i++) {
    t = 0;
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{16}
    inner:
    for (j = 0; j < 9; j++) {
      x = i - 4 + j;
      if ((((0 <= x) && (x < 8192))) && ((((0 <= filter[j]) && (filter[j] <= 255))))){
        t += ((orig[x]) * (filter[j]));
      }
    }
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    sol[i] = t;
  }
}