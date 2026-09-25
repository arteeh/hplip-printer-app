// SPDX-License-Identifier: Apache-2.0
#define _POSIX_C_SOURCE 200809L
#include "hplip-plugin-verify.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Do not invoke a shell: paths (including spaces and metacharacters) are data.
static int
run_gpg(const char *home, const char *key, const char *signature,
        const char *payload, const char *fingerprint)
{
  int pipes[2], status, good = 0, valid = 0, bad = 0;
  pid_t pid, waited;
  FILE *stream;
  char line[4096];

  if (pipe(pipes) < 0)
    return 0;
  if ((pid = fork()) < 0)
  {
    close(pipes[0]);
    close(pipes[1]);
    return 0;
  }
  if (!pid)
  {
    close(pipes[0]);
    if (dup2(pipes[1], STDOUT_FILENO) < 0)
      _exit(127);
    close(pipes[1]);
    if (key)
      execlp("gpg", "gpg", "--no-options", "--batch", "--no-tty",
             "--no-autostart", "--homedir", home, "--status-fd", "1",
             "--import", "--", key, (char *)NULL);
    else
      execlp("gpg", "gpg", "--no-options", "--batch", "--no-tty",
             "--no-autostart", "--homedir", home, "--status-fd", "1",
             "--no-auto-key-retrieve", "--no-auto-key-import",
             "--trust-model", "always", "--verify", "--", signature,
             payload, (char *)NULL);
    _exit(127);
  }
  close(pipes[1]);
  stream = fdopen(pipes[0], "r");
  if (!stream)
  {
    close(pipes[0]);
    bad = 1;
  }
  else
  {
    while (fgets(line, sizeof(line), stream))
    {
      char *save, *tag, *field;
      int index = 0, pinned = 0;
      if (!strchr(line, '\n'))
        bad = 1;
      if (strncmp(line, "[GNUPG:] ", 9))
        continue;
      tag = strtok_r(line + 9, " \r\n", &save);
      if (!tag)
        continue;
      if (!strcmp(tag, "GOODSIG"))
        good++;
      else if (!strcmp(tag, "VALIDSIG"))
      {
        // VALIDSIG's tenth field is the primary key fingerprint; the first
        // is the signing (possibly sub-)key. Never trust a UID or short key ID.
        while ((field = strtok_r(NULL, " \r\n", &save)))
        {
          index++;
          if (index == 1)
            pinned = !strcmp(field, fingerprint);
          if (index == 10)
            pinned = !strcmp(field, fingerprint);
        }
        if (index < 9 || !pinned)
          bad = 1;
        valid++;
      }
      else if (!strcmp(tag, "BADSIG") || !strcmp(tag, "ERRSIG") ||
               !strcmp(tag, "EXPSIG") || !strcmp(tag, "EXPKEYSIG") ||
               !strcmp(tag, "REVKEYSIG") || !strcmp(tag, "KEYEXPIRED") ||
               !strcmp(tag, "SIGEXPIRED") || !strcmp(tag, "KEYREVOKED") ||
               !strcmp(tag, "NODATA") || !strcmp(tag, "FAILURE") ||
               !strcmp(tag, "ERROR"))
        bad = 1;
    }
    if (ferror(stream))
      bad = 1;
    fclose(stream);
  }
  do
    waited = waitpid(pid, &status, 0);
  while (waited < 0 && errno == EINTR);
  return waited == pid && WIFEXITED(status) && WEXITSTATUS(status) == 0 &&
         !bad && (key || (good == 1 && valid == 1));
}

int
hplip_verify_plugin(const char *home, const char *key,
                    const char *fingerprint, const char *signature,
                    const char *payload)
{
  struct stat st;
  if (mkdir(home, 0700) < 0 && errno != EEXIST)
    return 0;
  // Reject symlinks and homes writable/readable by another account. The parent
  // is the application's persistent state directory, owned by its runtime UID.
  if (lstat(home, &st) < 0 || !S_ISDIR(st.st_mode) ||
      st.st_uid != geteuid() || (st.st_mode & 077) != 0)
    return 0;
  return run_gpg(home, key, NULL, NULL, fingerprint) &&
         run_gpg(home, NULL, signature, payload, fingerprint);
}
