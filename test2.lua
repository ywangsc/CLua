--#!/usr/bin/lua
print(_VERSION) 
require("gun") 
local myMath = require("myMath")
print (myMath.myabs(-5.11234)) 
print(square(1.414213598))
print(cube(5))