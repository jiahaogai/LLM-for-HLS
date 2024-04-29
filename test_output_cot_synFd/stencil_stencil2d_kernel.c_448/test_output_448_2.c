#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int k;
  int idx;
  int idx0;
  int idx1;
  int idx2;
  int idx3;
  int idx4;
  int idx5;
  int idx6;
  int idx7;
  int idx8;
  int sum;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{126}
  loopj:
/* Standardize from: for(j ... ) */
  for (j = 1; j < 32 + 1 - 1; j++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k ... ) */
    for (k = 1; k < 32 + 1 - 1; k++) {
      sum = 0.0;
      idx0 = (0 + -(32 - 1) + 1) + ((j + 0) * (32 + 0 - 1)) + ((k + 0) * (32 + 0 - 1) * (32 + 1 - 1));
      idx1 = (0 + -(32 - 1) + 1) + ((j + 0) * (32 + 0 - 1)) + ((k + 1) * (32 + 0 - 1) * (32 + 1 - 1));
      idx2 = (0 + -(32 - 1) + 1) + ((j + 0) * (32 + 0 - 1)) + ((k + 2) * (32 + 0 - 1) * (32 + 1 - 1));
      idx3 = (0 + -(32 - 1) + 1) + ((j + 0) * (32 + 0 - 1)) + ((k + 3) * (32 + 0 - 1) * (32 + 1 - 1));
      idx4 = (0 + -(32 - 1) + 1) + ((j + 0) * (32 + 0 - 1)) + ((k + 4) * (32 + 0 - 1) * (32 + 1 - 1));
      idx5 = (0 + -(32 - 1) + 1) + ((j + 0) * (32 + 0 - 1)) + ((k + 5) * (32 + 0 - 1) * (32 + 1 - 1));
      idx6 = (0 + -(32 - 1) + 1) + ((j + 0) * (32 + 0 - 1)) + ((k + 6) * (32 + 0 - 1) * (32 + 1 - 1));
      idx7 = (0 + -(32 - 1) + 1) + ((j + 0) * (32 + 0 - 1)) + ((k + 7) * (32 + 0 - 1) * (32 + 1 - 1));
      idx8 = (0 + -(32 - 1) + 1) + ((j + 0) * (32 + 0 - 1)) + ((k + 8) * (32 + 0 - 1) * (32 + 1 - 1));
      sum += filter[0] * orig[idx0];
      sum += filter[1] * orig[idx1];
      sum += filter[2] * orig[idx2];
      sum += filter[3] * orig[idx3];
      sum += filter[4] * orig[idx4];
      sum += filter[5] * orig[idx5];
      sum += filter[6] * orig[idx6];
      sum += filter[7] * orig[idx7];
      sum += filter[8] * orig[idx8];
      sol[idx0] = sum;
    }
  }
}