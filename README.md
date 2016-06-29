# Introduction
The library can be used to deal with big integers (integers only, not floating point numbers !! ) upto 3000 decimal digits long. Fortunately, the library is simple and easy to use. Unfortunately, it isn't vast in functionality at the moment. Also, the array of deciaml digits that are being allocated are not size adjusted which means, a 100 digit long number takes the same memory as a 3000 digit long number (3000*1=3000 bytes), meaning a lot of space is wasted actually. Multiplication and Division has been implemented using the long multiplication and long division methods respectively.

#License
Copyright (c) 2014, Aloy Gupta

All rights reserved.

BSD 3-Clause License
http://www.opensource.org/licenses/BSD-3-Clause

# Contact

Pointing out bugs is absolutely welcome.
Although, there are faster and robust third-party biginteger (and bigdecimal too !! ) libraries available in C, this was built mainly as a programming exercise, but is easy to use.

Aloy Gupta

aloygupta1993@gmail.com