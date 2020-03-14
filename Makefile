PROG =	getcwd
NOMAN =	getcwd

WARNINGS = Yes

BINDIR ?=	${HOME}/.local/bin
BINOWN ?!=	id -un
BINGRP ?!=	id -gn

.include <bsd.prog.mk>
