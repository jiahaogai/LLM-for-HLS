Code: #pragma ACCEL kernel

### Parameters

| Parameter | Abstracted? | Variadic? | Nested? | Function? | Const? |
| --------- | ----------- | --------- | ------ | -------- | ----- |
| orig | No | No | No | No | Yes |
| sol | No | No | No | No | No |
| filter | No | No | No | No | No |

### Local Variables

| Name | Size (Bits) | Type |
| ---- | ------------ | ---- |
| i |  | int |
| j |  | int |
| k |  | int |
| orig_idx |  | int |
| sol_idx |  | int |
| filter_idx |  | int |

### Static Variables

| Name | Size (Bits) | Type | Filename |
| ---- | ------------ | ---- | -------- |
| STEPS | 20 | int | stencil.c |
| FILTER_FACTOR | 8 | int | stencil.c |

### Functions

| Name | Summary |
| ---- | ------- |
| apply_filter |  |
| pad_sol |  |
| pad_orig |  |
| depad_sol |  |
| depad_orig |  |
| stencil |  |