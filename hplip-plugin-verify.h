// SPDX-License-Identifier: Apache-2.0
#ifndef HPLIP_PLUGIN_VERIFY_H
#define HPLIP_PLUGIN_VERIFY_H

// Import the packaged key offline and require an unexpired signature from the
// pinned primary fingerprint. Returns 1 only on successful verification.
int hplip_verify_plugin(const char *home, const char *key,
                        const char *fingerprint, const char *signature,
                        const char *payload);
#endif
