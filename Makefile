PROG =	getcwd
NOMAN =	getcwd
SCRIPT = getcwd-splitw getcwd-wrapper

WARNINGS = Yes

BINDIR ?=	${HOME}/.local/bin
BINOWN ?!=	id -un
BINGRP ?!=	id -gn

afterinstall:
.for F in ${SCRIPT}
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
		${.CURDIR}/${F}.sh ${DESTDIR}${BINDIR}/${F}
.endfor

.include <bsd.prog.mk>
