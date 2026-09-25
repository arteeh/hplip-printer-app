kind: compose
description: Strip development tooling from the HPLIP runtime artifact.

build-depends:
  - printer-app/runtime-stack.bst

config:
  exclude:
    - debug
    - devel
    - doc
    - locale
    - static-blocklist
    - tests
    - vm-only
