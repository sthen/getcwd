/*
 * Copyright (c) 2015 Ingo Schwarze <schwarze@openbsd.org>
 * Copyright (c) 2020 Stuart Henderson <stu@spacehopper.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * witH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/param.h>
#include <sys/sysctl.h>

#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <vis.h>
#include <unistd.h>
#include <wchar.h>

void mbswprint(const char *);
void curwd(pid_t);

void
mbswprint(const char *mbs)
{
	char	  buf[5];
	wchar_t	  wc;
	int	  len;  /* length in bytes of UTF-8 encoded string */
	int	  width;  /* display width of a single Unicode char */

	while (*mbs != '\0') {
		len = mbtowc(&wc, mbs, MB_CUR_MAX);
		if (len == -1) {
			(void)mbtowc(NULL, NULL, MB_CUR_MAX);
			len = 1;
		}
		if (len == 1)
			width = vis(buf, mbs[0],
			    VIS_TAB | VIS_NL | VIS_CSTYLE, mbs[1]) - buf;
		else if ((width = wcwidth(wc)) == -1) {
			/* U+FFFD replacement character */
			memcpy(buf, "\357\277\275\0", 4);
			width = 1;
		} else {
			memcpy(buf, mbs, len);
			buf[len] = '\0';
		}
		fputs(buf, stdout);
		mbs += len;
	}
	fputs("\n", stdout);
}

void
curwd(pid_t pid)
{
	int name[] = { CTL_KERN, KERN_PROC_CWD, pid };
	char path[PATH_MAX];
	size_t pathlen = sizeof path;

	if (sysctl(name, 3, path, &pathlen, NULL, 0) != 0)
		err(EXIT_FAILURE, "sysctl: %d", pid);

	mbswprint(path);
}

int
main(int argc, char *argv[])
{
	int pid;
	const char *errstr;

	if (pledge("stdio ps", "") == -1)
		err(EXIT_FAILURE, "pledge");

	if (argc != 2)
		errx(EXIT_FAILURE, "usage: getcwd <pid>");

	pid = strtonum(argv[1], 1, UINT_MAX, &errstr);
	if (errstr != NULL)
		errx(EXIT_FAILURE, "pid is %s: %s", errstr, argv[0]);

	curwd(pid);

	return EXIT_SUCCESS;
}
