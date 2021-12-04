# Bit-Stream-in-C

Two simple functions to write and read any given value, as bits, in a array.



Example:

``` 
30 -> 11110
14 -> 1110
6  -> 110

            | 30| 14 | 6|
bitstream = 11110111 0110XXXX
             byte 0   byte 1
```
