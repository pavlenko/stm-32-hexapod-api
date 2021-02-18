# Moving algorithm

- LF, LM, LR - front, middle, rear on left
- RF, RM, RR - front, middle, rear on right
- G - grounded
- F - floating
- 0.0 - moving diff

### TRIPOD GAIT (2 phases)

| I | P |   LF   |   LM   |   LR   |   RF   |   RM   |   RR   |
|---|---|--------|--------|--------|--------|--------|--------|
| 0 | 0 | G +0.0 | G +0.0 | G +0.0 | G +0.0 | G +0.0 | G +0.0 |
| 1 | 1 | F +0.5 | G -0.5 | F +0.5 | G -0.5 | F +0.5 | G -0.5 |
| 2 | 1 | G +1.0 | G -1.0 | G +1.0 | G -1.0 | G +1.0 | G -1.0 |
| 3 | 1 | G +0.5 | F -0.5 | G +0.5 | F -0.5 | G +0.5 | F -0.5 |
| 4 | 1 | G +0.0 | F +0.0 | G +0.0 | F +0.0 | G +0.0 | F +0.0 |
| 5 | 2 | G -0.5 | F +0.5 | G -0.5 | F +0.5 | G -0.5 | F +0.5 |
| 6 | 2 | G -1.0 | G +1.0 | G -1.0 | G +1.0 | G -1.0 | G +1.0 |
| 7 | 2 | F -0.5 | G +0.5 | F -0.5 | G +0.5 | F -0.5 | G +0.5 |
| 8 | 2 | F +0.0 | G +0.0 | F +0.0 | G +0.0 | F +0.0 | G +0.0 |

### RIPPLE GAIT (4 phases, +overlap)

| I |   LF   |   LM   |   LR   |   RF   |   RM   |   RR   |
|---|--------|--------|--------|--------|--------|--------|
| 0 | G +0.0 | G +0.0 | G +0.0 | G +0.0 | G +0.0 | G +0.0 |
| 1 | F | G | G | G | G | F |
| 2 | G | G | G | G | F | G |
| 3 | G | G | F | F | G | G |
| 4 | G | F | G | G | G | G |
| 5 | F | G | G | G | G | F |
| 6 | G | G | G | G | F | G |
