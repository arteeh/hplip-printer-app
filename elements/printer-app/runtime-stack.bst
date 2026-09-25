kind: stack
description: HPLIP print appliance with one canonical FSDK CUPS provider.

depends:
  - printer-app/application.bst
  - printer-app/hplip.bst
  - printer-app/net-snmp.bst
  - printer-app/python3-distro.bst
  - printer-app/runtime-files.bst
  - ghostscript-fsdk.bst:printer-app/pappl-retrofit.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:public-stacks/runtime-gnu.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/avahi.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/ca-certificates.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/catatonit.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/cups-daemon-only.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/cups-filters.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/dbus.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/ghostscript.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/gnupg.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/gzip.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/grep.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/libcupsfilters.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/libppd.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/mutool.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/perl.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/python3.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/python3-dbus.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/python3-pil.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/pygobject.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/which.bst
  - ghostscript-fsdk.bst:freedesktop-sdk.bst:components/xz.bst
