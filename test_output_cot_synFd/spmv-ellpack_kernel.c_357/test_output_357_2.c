Code: #pragma ACCEL kernel

void ellpack(double nzval[4940],int cols[4940],double vec[494],double out[494])
{
  int i;
  int j;
  for (i = 0; i < 494; i++) 
    out[i] = ((double )0);
  
#pragma ACCEL PIPELINE auto{}
  
#pragma ACCEL TILE FACTOR=auto{4}
  
#pragma ACCEL PARALLEL FACTOR=auto{16}
  for (j = 0; j < 50; j++) {
    
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
    for (i = 0; i < 40; i++) {
      out[cols[j * 40 + i]] += nzval[j * 40 + i] * vec[j];
    }
  }
}
Error: /root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:2:4: error: unknown type name ‘Kernel’
    2 |  Kernel
      |    ^^^^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘#’ in program
    4 | 6. #pragma ACCEL PIPELINE auto{}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘#’ in program
    4 | 6. #pragma ACCEL TILE FACTOR=auto{4}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:4:4: error: stray ‘#’ in program
    4 | 6. #pragma ACCEL PARALLEL FACTOR=auto{16}
      |    ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:5: error: stray ‘#’ in program
    7 |   for (i = 0; i < 494; i++) {
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:7:5: error: stray ‘#’ in program
    7 |   out[i] = ((double )0);
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:10:3: error: stray ‘#’ in program
   10 | 6. #pragma ACCEL PIPELINE auto{}
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:10:3: error: stray ‘#’ in program
   10 | 6. #pragma ACCEL TILE FACTOR=auto{4}
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:10:3: error: stray ‘#’ in program
   10 | 6. #pragma ACCEL PARALLEL FACTOR=auto{16}
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:11:5: error: stray ‘#’ in program
   11 |   for (j = 0; j < 50; j++) {
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:11:5: error: stray ‘#’ in program
   11 |     
#pragma ACCEL PARALLEL reduction=out FACTOR=auto{16}
      |   ^
/root/autodl-tmp/LLM/LLM-for-HLS/tmp.c:11:5: error: stray ‘#’ in program
   11 |     
#pragma ACCEL PARALLEL reduction=out FACTOR=auto