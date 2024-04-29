**Mappings:**

  | Variable | Sizes    |  Dope View  |
|------------|---------------|-----------------|
| orig       | 8192          | 0               |
| sol        | 8192          | 0               |
| filter     | 9             | 0               |


  | View                    | Var        | Sizes    | Dope View                       |
|---------------------------|------------|----------|----------------------------------|
| __original                | orig       | 8192     | __original                       |
|                           |           |          |                                  |
| __transformed             | sol        | 8192     | __transformed                    |
|                           |           |          |                                  |
| filter                    | filter     | 9        | filter                           |
|===========================+============+==========+==================================|

  
#pragma ACCEL kernel

void stencil(int orig[8192],int sol[8192],int filter[9])
{
  int i;
  int j;
  int bi;
  int bj;
  int ai;
  int aj;
  int ti;
  int tj;
  int val;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  outer:
  for (i = 0; i < 8; i++) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{62}
    middle:
    for (j = 0; j < 8; j++) {
      bi = i * 64;
      bj = j * 64;
      val = 0;
      
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{16}
      inner:
      for (ti = 0; ti < 8; ti++) {
        
#pragma ACCEL PARALLEL reduction=val FACTOR=auto{16}
        inner_1:
        for (tj = 0; tj < 8; tj++) {
          ai = ti * 8 + bi;
          aj = tj * 8 + bj;
          val += orig[ai + aj] * filter[ti * 8 + tj];
        }
      }
      sol[bi + bj] = val;
    }
  }
}