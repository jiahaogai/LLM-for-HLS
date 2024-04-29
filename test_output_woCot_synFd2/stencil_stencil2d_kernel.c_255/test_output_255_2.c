#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[3][3])
{
  int i;
  int j;
  int ti;
  int tj;
  int fi;
  int fj;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 1; i < 400 - 1; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{8}
    for (j = 1; j < 400 - 1; j++) {
      val = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (ti = i - 1; ti <= i + 1; ti++) {
        
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
        for (tj = j - 1; tj <= j + 1; tj++) {
          fi = ti - i + 1;
          fj = tj - j + 1;
          val += filter[fi][fj] * orig[ti][tj];
        }
      }
      sol[i][j] = val;
    }
  }
}