PROG =	getcwd
NOMAN =	getcwd
SCRIPT = getcwd-splitw.sh

WARNINGS = Yes

BINDIR ?=	${HOME}/.local/bin
BINOWN ?!=	id -un
BINGRP ?!=	id -gn

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
		${.CURDIR}/${SCRIPT} ${DESTDIR}${BINDIR}/getcwd-splitw

.include <bsd.prog.mk>
