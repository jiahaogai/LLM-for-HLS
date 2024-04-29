#pragma ACCEL kernel

void stencil(int orig[400][400],int sol[400][400],int filter[25])
{
  int row;
  int column;
  int i;
  int j;
  int value;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopj:
/* Standardize from: for(j = 1; j < 400 - 1; j++) {...} */
  for (j = 1; j <= 398; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopi:
/* Standardize from: for(i = 1; i < 400 - 1; i++) {...} */
    for (i = 1; i <= 398; i++) {
      value = ((orig[j][i - 1] + orig[j][i + 1]) + (orig[j - 1][i] + orig[j + 1][i])) + orig[j][i];
      sol[j][i] = value;
/*
      if(value < 0){
        value = 0;
      }
      else if(value > 255){
        value = 255;
      }
      sol[j][i] = value;
*/
    }
  }
}