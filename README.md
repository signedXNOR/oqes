# oqes
(Hopefully) (Somewhat) True Random Number Generator password generator in C using Windows' cryptograpy sdk thing (bcrypt)
It's C, and it's written by me so there might be memory leaks or other such C shenanigans.
Other than that, it's *finished*. Should do the trick. If you're on Windows, that is.

Also, it's version 2 cause there was a previous version, which wasn't as secure cuz it was using only the c standard library's `rand()` function for randomness, while this version uses are true-enough random generator to seed the pseudorandom generator.
