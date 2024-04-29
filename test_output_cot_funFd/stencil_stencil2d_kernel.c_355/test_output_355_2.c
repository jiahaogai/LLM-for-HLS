#pragma ACCEL PIPELINE auto{off}
 #pragma ACCEL TILE FACTOR=auto{8}
 #pragma ACCEL PARALLEL FACTOR=auto{14}

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int result = 0;
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{4}
  for (i = 1; i < 8191; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    for (j = 1; j < 8191; j++) {
      result = 0;
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      for (k = 0; k < 9; k++) {
        result += orig[i + ((k - 4) * 8192)] [j + ((k - 4) * 8192)] * filter[k];
      }
      sol[i][j] = result;
    }
  }
}