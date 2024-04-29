Code: ### Parameters:
 
alpha  
A scalar used in multiplication operations that appear in the kernel.  
beta   
A scalar used in multiplication operations that appear in the kernel.  
C      
A 2D input matrix that appears in the kernel.  
A      
A 2D input matrix that appears in the kernel.  
B      
A 2D input matrix that appears in the kernel.  
  
### Local Variables:
 
temp1  
A local variable that appears in the kernel.  
temp2  
A local variable that appears in the kernel.  
  
### Global Variables:
 
C      
A global variable that appears in the kernel.  
A      
A global variable that appears in the kernel.  
B      
A global variable that appears in the kernel.  
 
#pragma ACCEL kernel

### Function Definitions:

### LOOP_60
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  loop_60:
  for (int i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loop_59:
    for (int j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loop_58:
    for (int j = 0; j < 60; j++) {
      
#pragma ACCEL PARALLEL reduction=temp2 FACTOR=auto{__PARA__L3}
      loop_57:
      for (int k = 0; k < 60; k++) {
        double temp2 = 0.0;
        loop_54:
        for (int l = 0; l < 80; l++) {
          temp2 += A[i][k] * B[k][l];
        }
	C[i][l] += alpha * temp2;
      }
    }
  }
}
Error: 
Please check the code and try again.
Code: ### Parameters:
 
alpha  
A scalar used in multiplication operations that appear in the kernel.  
beta   
A scalar used in multiplication operations that appear in the kernel.  
C      
A 2D input matrix that appears in the kernel.  
A      
A 2D input matrix that appears in the kernel.  
B      
A 2D input matrix that appears in the kernel.  
  
### Local Variables:
 
temp1  
A local variable that appears in the kernel.  
temp2  
A local variable that appears in the kernel.  
  
### Global Variables:
 
C      
A global variable that appears in the kernel.  
A      
A global variable that appears in the kernel.  
B      
A global variable that appears in the kernel.  
 
#pragma ACCEL kernel

### Function Definitions:

### LOOP_60
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{15}
  loop_60:
  for (int i = 0; i < 60; i++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{4}
    loop_59:
    for (int j = 0; j < 80; j++) {
      C[i][j] *= beta;
    }
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{32}
    loop_58:
    for (int j = 0; j <