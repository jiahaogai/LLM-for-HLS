#pragma ACCEL kernel

void stencil3d(double C0,double C1,double orig[2][2][2],double sol[2][2][2])
{
  int t1;
  int t2;
  int t3;
  int i;
  int j;
  int k;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (t1 = 0; t1 < 2; t1++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (t2 = 0; t2 < 2; t2++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (t3 = 0; t3 < 2; t3++) {
        sol[t1][t2][t3] = 0.0;
        i = 0;
        
#pragma ACCEL PARALLEL FACTOR=auto{2}
        while (i < 2) {
          j = 0;
          
#pragma ACCEL PARALLEL FACTOR=auto{2}
          while (j < 2) {
            k = 0;
            
#pragma ACCEL PARALLEL FACTOR=auto{2}
            while (k < 2) {
              sol[t1][t2][t3] += 
                C0 * orig[t1][i][k] * orig[t1][j][k] + 
                C1 * orig[t1][i][k] * orig[t2][j][k];
              k++;
            }
            j++;
          }
          i++;
        }
      }
    }
  }
//#pragma endscop
}