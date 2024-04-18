7. `#pragma ACCEL PIPELINE auto{__PIPE__L2}` - Automatically pipeline the loops for this for loop.

#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{1}

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (i = 0; i < 400; i++) {
    x1[i] = ((double )0);
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{20}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L4}
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * y_1[j];
    }
	x1[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  for (i = 0; i < 400; i++) {
    double sum = ((double )0);
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{__PARA__L5}
    for (j = 0; j < 400; j++) {
      sum += A[j][i] * y_2[j];
    }
	x2[i] = sum;
  }
}