#===============================================================================
# Copyright 2012.
# Scott Alexander Holm.
# All Rights Reserved.
#===============================================================================
 

BORLAND_HOME = c:/apps/borlandC

.SUFFIXES : .cxx .obj .exe

all : objs bins 
#run

SRCS = \
	main.cxx \
	game.cxx \
	play.cxx \
	confederateplay.cxx \
	card.cxx \
	deck.cxx \
	cribhand.cxx \
	hand.cxx \
	humanplayer.cxx \
	computerplayer.cxx \
	confederateplayer.cxx \
	player.cxx

OBJS = ${SRCS:.cxx=.obj}

#OBJS = \
#	main.obj \
#	game.obj \
#	play.obj \
#	confederateplay.obj \
#	card.obj \
#	deck.obj \
#	cribhand.obj \
#	hand.obj \
#	humanplayer.obj \
#	computerplayer.obj \
#	confederateplayer.obj \
#	player.obj

.cxx.obj :
	${BORLAND_HOME}/bin/bcc32.exe -P -I${BORLAND_HOME}/include \
	    -L${BORLAND_HOME}/lib -c $<
.obj.exe :
	${BORLAND_HOME}/bin/bcc32.exe -P -I${BORLAND_HOME}/include \
	    -L${BORLAND_HOME}/lib ${OBJS}
#.obj.exe :
#	${BORLAND_HOME}/bin/bcc32.exe -P -I${BORLAND_HOME}/include \
#	    -L${BORLAND_HOME}/lib ${OBJS}
objs : ${OBJS}


#	${BORLAND_HOME}/bin/bcc32.exe -P -I${BORLAND_HOME}/include \
#	    -L${BORLAND_HOME}/lib -c ${SRCS}

main.exe : ${OBJS}

bins : main.exe

run :
	main.exe


clean :
	del *.cxx~
	del Makefile~
	del *.h~
	del *.exe
	del *.obj
	del *.tds
	del *.swp
	del *.ilc
	del *.ild
	del *.ilf
	del *.ils
	del *.map
	del *.i


