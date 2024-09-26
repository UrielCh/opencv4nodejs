# changelog

## Version 7.2.0
- @see github

## Version 7.1.2
- @see github

## Version 7.1.1
- update deps versions
- support for vcpkg binary

## Version 7.1.0
- update deps versions
- Add bindings for row, rowRange, col, colRange [PR-108](https://github.com/UrielCh/opencv4nodejs/pull/150)

## Version 7.0.0
- Updated code to ESM.
- Introduced new exports model.
- Fixed typing errors.
- Added missing types.
- Removed typing duplication in codebase.
- Native code is now generated directly by the default node-gyp rebuild.
- GitHub actions now test all available Windows, macOS, and Linux environments.

## Version 6.6.0
- update gcc flag to enable C++ 17
- fix code to support latest onpenCV version up to 4.9

## Version 6.5.3
-  add cv.magnitude [PR-118](https://github.com/UrielCh/opencv4nodejs/pull/118)
-  documentation [PR-108](https://github.com/UrielCh/opencv4nodejs/pull/108)

## Version 6.5.2
- fix typing error

## Version 6.5.1
- patch imencode electron 21+ memory cage 
- patch add mask option to the detect function

## Version 6.5.0
- integrate native-node-utils code inside cc/native-node-utils
- add comments in native-node-utils
- add cv.min cv.max

## Version 6.4.5
- drop .ts files from npm package.
- add .d.ts file for ts files in npm package.
- add .d.ts.map file for ts files in npm package.
- fix [issue 81](https://github.com/UrielCh/opencv4nodejs/issues/81)
  
## Version 6.4.4
- remove typescript requirement at setup [PR-78](https://github.com/UrielCh/opencv4nodejs/pull/78)
- [PR-80](https://github.com/UrielCh/opencv4nodejs/pull/80)

## Version 6.4.3
- update dependencies

## Version 6.4.2
- update dependencies

## Version 6.4.1
- add Mat.ones
- add Mat.zeros
- start splitting tests.

## Version 6.4.0
- refactor test
- fix types errors
- add img_hash PR#65
- use new @u4/opencv-build@0.7.3 (unnecessary builds, add a sym-link latest build directory)

## Version 6.3.0
* use new @u4/opencv-build@0.6.1
* improve cuda support add `--cudaArch <value>` to choose your cuda target, for example I use --cudaArch=8.6 for my RTX 3060, check https://en.wikipedia.org/wiki/CUDA for full list.
* `build-opencv` support a new action: `list` that will list ixisting openCV build
* `build-opencv auto` will not rebuild anything if the current build is working 

## Version 6.2.5
* update @u4/opencv-build
* replace tiny-glob by @u4/tiny-glob

## Version 6.2.4
* update @u4/opencv-build

## Version 6.2.3
* update @u4/opencv-build

## Version 6.2.2
* update deps including @u4/opencv-build
* autobuild now work out of the box on common setup. (chocolatey, brew, apt)

## Version 6.2.1
* fix error message annalyse in cvLoader
* add startWindowThread()

## Version 6.2.0
* PR https://github.com/UrielCh/opencv4nodejs/pull/37
* add support for 1, 3 and 4 dimmentionals Mat
* improve debug binding usability

## Version 6.1.6
* fix issues/33 

## Version 6.1.5

* dump deps versions
* improve dry-run
* add toMatTypeName() function
* add template samples
* add cv.getScoreMax()
* add cv.dropOverlappingZone()
* add Net.dump() mapping
  
## Version 6.1.4

* Tested an works with all openCV version from 3.2.0 to 4.5.5
* small patches
* new build system, retrocompatible with origial justadudewhohacks/opencv4nodejs

## Version 6.1.3

* fix linux build regression [PR14](https://github.com/UrielCh/opencv4nodejs/pull/14)

## Version 6.1.2

* add `--node-gyp-options=<options>` param in compilation script [PR11](https://github.com/UrielCh/opencv4nodejs/pull/11)
* add doc in code
* rename _binding.gyp to binding.gyp and add a dummy "install" script
* add missing dev dependency
* improve compilation output log
* improve --dry-run mode
* bump dependencies versions

## Version 6.1.1

* fix ambiguous typing
* restructure examples
* add some bindings
* add AgeGender from [spmallick/learnopencv](https://github.com/spmallick/learnopencv/blob/master/AgeGender/)
* add ObjectDetection-YOLO from [spmallick/learnopencv](https://github.com/spmallick/learnopencv/blob/master/ObjectDetection-YOLO/)

## Version 6.1.0

* [breaking change] build-opencv action argument build is now renamed rebuild, and build, clean, configure ar now available.
* [breaking change] build-opencv -j alias of --job if gone
* testing are now converted to Typescript
* fix Typing
* fix getRegion() cordump
* add doc

## Version 6.0.12

* fix missing imports

## Version 6.0.11

* fix drawUtils.ts code
* use @u4/opencv-build 0.4.3
* add some more cv types
* start refactor cv.d.ts
* drop enum usage type WND_PROP

## Version 6.0.10

* add highgui modules
* add setWindowProperty, getWindowProperty, setWindowTitle function
* update cpp standard version to fix modern electron support

## Version 6.0.9

* enable nan module worker
* compatible with electron 9+
* add --vscode argument to generate vscode c_cpp_properties.json

## Version 6.0.8

* add support for Electron
* cleaner logs

## Version 6.0.7

* bump dependence versions inclkuding @u4/opencv-build@0.4.1
* [Fix typyings in Net.d.ts](https://github.com/UrielCh/opencv4nodejs/pull/3)
