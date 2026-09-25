kind: junction

sources:
  - kind: git_repo
    url: github:projectbluefin/ghostscript-printer-app.git
    track: testing
    ref: f36174f27f5bb08421712bd77680cbddfc71862e

config:
  options:
    arch: "%{arch}"
