| branch | travis | appveyor |
| :---: | :---: | :---: |
| master | [![Build Status](https://travis-ci.org/raytracingDevTeam/raytracing.svg?branch=master)](https://travis-ci.org/raytracingDevTeam/raytracing) | [![Build status](https://ci.appveyor.com/api/projects/status/1mi2agvpc8ln8ffi/branch/master?svg=true)](https://ci.appveyor.com/project/andrearastelli/raytracing/branch/master) |
| develop | [![Build Status](https://travis-ci.org/raytracingDevTeam/raytracing.svg?branch=develop)](https://travis-ci.org/raytracingDevTeam/raytracing) | [![Build status](https://ci.appveyor.com/api/projects/status/1mi2agvpc8ln8ffi/branch/master?svg=true)](https://ci.appveyor.com/project/andrearastelli/raytracing/branch/develop) |
| all || [![Build status](https://ci.appveyor.com/api/projects/status/1mi2agvpc8ln8ffi?svg=true)](https://ci.appveyor.com/project/andrearastelli/raytracing) |

# Raytracing in One Weekend and beyond

## 2.0.0
![Imgur](https://i.imgur.com/5SPowYd.png)

Image info:
- Cornell box with volumes
- Samples per pixel 512
- Image resolution 400x400
- Single Thread / SIMD instruction

## 1.0.0
![Imgur](https://i.imgur.com/KLX1Kv6.png)

Image info:
- Total rendering time 216s (on windows)
- Samples per pixel 128
- Image resolution 800x400 px
- Single thread

> In the current image, with the current sample count, will be extremely diffucult to identify metal from lambert materials, but with a higher (and most reasonable) sample count, let's say 128 or even 64, the total amount of rays generated will be 1.966.080.000, almost 2 Billion (128 sample, with 64 will be 1 Billion), and for a single threaded application this may be a little overkill.


## References
- [Raytracing in a Weekend](http://amzn.eu/3JyrhOX)
