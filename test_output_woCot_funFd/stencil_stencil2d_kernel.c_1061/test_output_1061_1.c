#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int ti;
  int tj;
  int bi;
  int bj;
  int fi;
  int fj;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      ti = -1 + 8 * (i / 8);
      tj = -1 + 8 * (j / 8);
      bi = i - ti * 8;
      bj = j - tj * 8;
      val = 0;
      
#pragma ACCEL PIPELINE auto{flatten}
      
#pragma ACCEL TILE FACTOR=auto{62}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (fi = 0; fi < 9; fi++) {
        
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{1}
        for (fj = 0; fj < 9; fj++) {
          val += filter[fi * 9 + fj] * orig[ti + fi][tj + fj];
        }
      }
      sol[bi][bj] = val;
    }
  }
}