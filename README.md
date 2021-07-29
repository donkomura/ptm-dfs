# ptm-dfs
distributed file system using PTMDB

## Requirements

### packages

* boost
	- program-options
	- mpi, serialization
* quill
* mpi
* thallium

### environmental variables

* `PKG_LOCAL_ROOT`
	- `Quill` installed location

## build

```sh
$ mkdir build
$ cd build
$ cmake -DPM_FILE_NAME='"\"/dev/dax0.1\""' ..
```

### cmake options

```sh
// pwd is a CLFLUSH and pfence/psync is nops (default)
USE_PWB_IS_CLFLUSH:BOOL=OFF

// pwd is a CLFLUSHOPT and pfence/psync are SFENCE
USE_PWB_IS_CLFLUSHOPT:BOOL=OFF

// pwd is a CLWB and pfence/psync are SFENCE
USE_PWB_IS_CLWB:BOOL=OFF

// pwd/pfence/psync is nops
USE_PWB_IS_NOP:BOOL=ON

// use DuoVRFC
USE_DUO_VR_FC:BOOL=OFF

// use Romulus log
USE_ROMULUS_LOG:BOOL=OFF

// use TrinityVRFC
USE_TRINITY_VR_FC:BOOL=OFF

// use TrinityVRTL2
USE_TRINITY_VR_TL2:BOOL=ON

// persistent memory device file for ptmdb
PM_FILE_NAME:STR
```

