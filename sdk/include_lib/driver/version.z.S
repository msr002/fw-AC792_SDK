.section .sys.version, "ax"

.global include_lib_driver_version

include_lib_driver_version:

.asciz "INCLUDE_DRIVER-$1a2b09f"
