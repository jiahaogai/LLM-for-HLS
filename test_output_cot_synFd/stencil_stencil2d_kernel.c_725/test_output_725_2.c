#pragma ACCEL kernel

void stencil(int orig[4][4],int sol[4][4],int filter[3][3])
{
  int i;
  int j;
  int fl;
  int ol;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 4; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 0; j < 4; j++) {
      sol[i][j] = 0;
      fl = 0;
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (ol = 0; ol < 3; ol++) {
        
#pragma ACCEL PARALLEL FACTOR=auto{1}
        for (fl = 0; fl < 3; fl++) {
          sol[i][j] += filter[fl][ol] * orig[i + fl - 1][j + ol - 1];
        }
      }
    }
  }
}