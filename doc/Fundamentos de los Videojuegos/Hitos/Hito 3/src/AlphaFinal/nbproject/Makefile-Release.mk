#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Interfaz.o \
	${OBJECTDIR}/Menu.o \
	${OBJECTDIR}/aro.o \
	${OBJECTDIR}/boss.o \
	${OBJECTDIR}/enemigos.o \
	${OBJECTDIR}/juego.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mapGame.o \
	${OBJECTDIR}/player.o \
	${OBJECTDIR}/renderWindow.o \
	${OBJECTDIR}/sprite.o \
	${OBJECTDIR}/state.o \
	${OBJECTDIR}/textura.o \
	${OBJECTDIR}/vector2f.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu /usr/lib/x86_64-linux-gnu/libsfml-audio.so /usr/lib/x86_64-linux-gnu/libsfml-graphics.so /usr/lib/x86_64-linux-gnu/libsfml-system.so /usr/lib/x86_64-linux-gnu/libsfml-window.so /usr/lib/x86_64-linux-gnu/libtinyxml.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alphafinal

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alphafinal: /usr/lib/x86_64-linux-gnu/libsfml-audio.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alphafinal: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alphafinal: /usr/lib/x86_64-linux-gnu/libsfml-system.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alphafinal: /usr/lib/x86_64-linux-gnu/libsfml-window.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alphafinal: /usr/lib/x86_64-linux-gnu/libtinyxml.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alphafinal: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alphafinal ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Interfaz.o: Interfaz.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Interfaz.o Interfaz.cpp

${OBJECTDIR}/Menu.o: Menu.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Menu.o Menu.cpp

${OBJECTDIR}/aro.o: aro.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/aro.o aro.cpp

${OBJECTDIR}/boss.o: boss.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/boss.o boss.cpp

${OBJECTDIR}/enemigos.o: enemigos.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/enemigos.o enemigos.cpp

${OBJECTDIR}/juego.o: juego.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/juego.o juego.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/mapGame.o: mapGame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mapGame.o mapGame.cpp

${OBJECTDIR}/player.o: player.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/player.o player.cpp

${OBJECTDIR}/renderWindow.o: renderWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/renderWindow.o renderWindow.cpp

${OBJECTDIR}/sprite.o: sprite.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sprite.o sprite.cpp

${OBJECTDIR}/state.o: state.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/state.o state.cpp

${OBJECTDIR}/textura.o: textura.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/textura.o textura.cpp

${OBJECTDIR}/vector2f.o: vector2f.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DSFML_STATIC -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vector2f.o vector2f.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alphafinal

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
