# Block Ciphers for =nil; Foundation's Cryptography Suite
[![Build Status](https://travis-ci.com/NilFoundation/block.svg?branch=master)](https://travis-ci.com/NilFoundation/block)

Crypto3 Block cipher library extends the =nil; Foundation's cryptography suite. The library
implements common block cipher implementations such as aes, shacal.. The library supports
API to encrypt/decrypt data and supports streaming data as input via supporting accumulators
from boost library.


## Repository structure
```
root
├── cmake: cmake sub-module with helper functions/macros to build crypto3 library umbrella-repository
├── docs: documentation , tutorials and guides
├── test: Unit test cases
├── include/nil/crypto3: Library source 
│   ├── block : block cipher impmentation
│   │   ├── accumulators: implemtation of accumulators used internally
│   │   ├── adaptor: TODO
│   │   ├── algorithm: encryption/decryption algorithms
│   │   ├── detail: helper functions, constants , misc common utils. 
│   ├── detail : helper functions, constants , misc common utils.
```


## Building

This library uses Boost CMake build modules (https://github.com/BoostCMake/cmake_modules.git). 
To actually include this library in a project it is required to:

1. Add [CMake Modules](https://github.com/BoostCMake/cmake_modules.git) as submodule to target project repository.
2. Add all the internal dependencies using [CMake Modules](https://github.com/BoostCMake/cmake_modules.git) as submodules to target project repository.
3. Initialize parent project with [CMake Modules](https://github.com/BoostCMake/cmake_modules.git) (Look at [crypto3](https://github.com/nilfoundation/crypto3.git) for the example)

## Dependencies

### Internal

* [Predef](https://github.com/nilfoundation/predef.git) (until https://github.com/boostorg/predef/pull/108 and https://github.com/boostorg/predef/pull/107 are accepted)

### External
* [Boost](https://boost.org) (>= 1.58)
