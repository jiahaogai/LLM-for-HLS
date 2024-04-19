### ACCEL PIPELINE auto{flatten}

### ACCEL TILE FACTOR=auto{1}
 
### ACCEL PARALLEL FACTOR=auto{1}
 
### ACCEL PARALLEL reduction = x1 FACTOR=auto{1}
 
### ACCEL PIPELINE auto{}

### ACCEL TILE FACTOR=auto{1}
 
### ACCEL PARALLEL FACTOR=auto{10}
 
### ACCEL PARALLEL reduction = x2 FACTOR=auto{20}
 
#pragma ACCEL kernel

void kernel_mvt(double x1[400],double x2[400],double y_1[400],double y_2[400],double A[400][400])
{
  int i;
  int j;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{flatten}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  for (i = 0; i < 400; i++) {
    double sum = y_1[i];
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{1}
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * x1[j];
    }
    y_2[i] = sum;
  }
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{10}
  for (i = 0; i < 400; i++) {
    double sum = y_2[i];
    
#pragma ACCEL PARALLEL reduction=sum FACTOR=auto{20}
    for (j = 0; j < 400; j++) {
      sum += A[i][j] * x2[j];
    }
    x1[i] = sum;
  }
//#pragma endscop
}