Code: #pragma ACCEL kernel

void stencil3d(double C0,double C1,double orig[2][2][2],double sol[2][2][2])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 0; r < 2; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 2; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 2; p++) {
        for (s = 0; s < 2; s++) ((sol)[r][q][p]) += ((C0)[s]) * ((orig)[r][q][p - 1]) + ((C1)[s]) * ((orig)[r][q][p]);
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil3d’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:25:58: error: subscripted value is neither array nor pointer nor vector
   25 |         for (s = 0; s < 2; s++) ((sol)[r][q][p]) += ((C0)[s]) * ((orig)[r][q][p - 1]) + ((C1)[s]) * ((orig)[r][q][p]);
      |                                                          ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil3d(char C0,char C1,char orig[2][2][2],char sol[2][2][2])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{8}
  for (r = 0; r < 2; r++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    for (q = 0; q < 2; q++) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (p = 0; p < 2; p++) {
        for (s = 0; s < 2; s++) ((sol)[r][q][p]) += ((C0)[s]) * ((orig)[r][q][p - 1]) + ((C1)[s]) * ((orig)[r][q][p]);
      }
    }
  }
//#pragma endscop
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c: In function ‘stencil3d’:
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:25:58: error: subscripted value is neither array nor pointer nor vector
   25 |         for (s = 0; s < 2; s++) ((sol)[r][q][p]) += ((C0)[s]) * ((orig)[r][q][p - 1]) + ((C1)[s]) * ((orig)[r][q][p]);
      |                                                          ^

Please check the code and try again.
Code: #pragma ACCEL kernel

void stencil3d(double C0,double C1,double orig[2][2][2],double sol[2][2][2])
{
  int r;
  int q;
  int p;
  int s;
//#pragma scop
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma