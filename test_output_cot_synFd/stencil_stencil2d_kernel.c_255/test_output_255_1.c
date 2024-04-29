#pragma ACCEL kernel

void stencil(int orig[400],int sol[400],int filter[9])
{
  int i;
  int j;
  int fl;
  int o;
  int s;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 400 - 1; j++) {
      o = orig[i * 400 + j];
      s = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (fl = 0; fl < 9; fl++) {
        s += o + ((-1 + fl % 3) * 400) + ((-1 + fl / 3)) + filter[fl];
      }
      sol[i * 400 + j] = s;
    }
  }
}