## MST/TSP Calculator
------------------------------------------------------------

After downloading and extracting the zip, type `source run.sh` to begin compilation

To run the program:

./calculate -m \<mode\> < \< mode_specified_file\>

There are three modes to this calculator:

1. Minimum Spanning Tree (MST)

2. Fast Traveling Sales Problem (FASTTSP)

3. Optimal Traveling Sales Problem (OPTTSP) -- WITH PRUNING

ex:


./calculate -m MST < MST_1.txt

./calculate -m FASTTSP < FASTTSTP_1.txt

./calculate -m OPTTSP < OPTTSP_1.txt


## Custom Built MST, FASTTSP, OPTTSP Files
----------------------------------------------------------------

```\< Number of total Locations\>

x_coord, y_coord (of location)

x_coord, y_coord (of location)

x_coord, y_coord (of location)
...
```


ex:

`cat mode_specified_file`

```
5

1 3

2 6

3 6

1 8

9 0
```

**Important to note that there are 5 Locations so this MUST mean there are 5 x,y coordinate pairs**

