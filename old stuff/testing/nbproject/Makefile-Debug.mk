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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Day.o \
	${OBJECTDIR}/src/Heat.o \
	${OBJECTDIR}/src/Settings.o \
	${OBJECTDIR}/src/WiFiSettings.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-export-dynamic -pthread -g
CXXFLAGS=-export-dynamic -pthread -g

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lgtk-3 -lgtkmm-3.0

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testing

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testing: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testing ${OBJECTFILES} ${LDLIBSOPTIONS} -export-dynamic -lgtkmm-3.0 -latkmm-1.6 -lgdkmm-3.0 -lgiomm-2.4 -lpangomm-1.4 -lglibmm-2.4 -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lgio-2.0 -lcairomm-1.0 -lcairo -lsigc-2.0 -lgdk_pixbuf-2.0 -lgobject-2.0 -lglib-2.0 -s

${OBJECTDIR}/src/Day.o: src/Day.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/gtkmm-3.0 -I/usr/include/atkmm-1.6 -I/usr/include/atk-1.0 -I/usr/include/glib-2.0 -I/usr/include/glibmm-2.4 -I/usr/include/sigc++-2.0 -I/usr/include/giomm-2.4 -I/usr/include/blkid -I/usr/include/uuid -I/usr/include/pangomm-1.4 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/gtk-3.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/libdrm -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/include/gtk-3.0/unix-print -I/usr/include/at-spi2-atk/2.0 -I/usr/include/gdkmm-3.0 -I/usr/include/cairomm-1.0 -I/usr/lib/gdkmm-3.0/include -I/usr/lib/gtkmm-3.0/include -I/usr/lib/glib-2.0/include -I/usr/lib/libffi-3.2.1/include -I/usr/lib/glibmm-2.4/include -I/usr/lib/sigc++-2.0/include -I/usr/lib/giomm-2.4/include -I/usr/lib/pangomm-1.4/include -I/usr/lib/cairomm-1.0/include -I/usr/lib/dbus-1.0/include -I/usr/include/c++ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Day.o src/Day.cpp

${OBJECTDIR}/src/Heat.o: src/Heat.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/gtkmm-3.0 -I/usr/include/atkmm-1.6 -I/usr/include/atk-1.0 -I/usr/include/glib-2.0 -I/usr/include/glibmm-2.4 -I/usr/include/sigc++-2.0 -I/usr/include/giomm-2.4 -I/usr/include/blkid -I/usr/include/uuid -I/usr/include/pangomm-1.4 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/gtk-3.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/libdrm -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/include/gtk-3.0/unix-print -I/usr/include/at-spi2-atk/2.0 -I/usr/include/gdkmm-3.0 -I/usr/include/cairomm-1.0 -I/usr/lib/gdkmm-3.0/include -I/usr/lib/gtkmm-3.0/include -I/usr/lib/glib-2.0/include -I/usr/lib/libffi-3.2.1/include -I/usr/lib/glibmm-2.4/include -I/usr/lib/sigc++-2.0/include -I/usr/lib/giomm-2.4/include -I/usr/lib/pangomm-1.4/include -I/usr/lib/cairomm-1.0/include -I/usr/lib/dbus-1.0/include -I/usr/include/c++ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Heat.o src/Heat.cpp

${OBJECTDIR}/src/Settings.o: src/Settings.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/gtkmm-3.0 -I/usr/include/atkmm-1.6 -I/usr/include/atk-1.0 -I/usr/include/glib-2.0 -I/usr/include/glibmm-2.4 -I/usr/include/sigc++-2.0 -I/usr/include/giomm-2.4 -I/usr/include/blkid -I/usr/include/uuid -I/usr/include/pangomm-1.4 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/gtk-3.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/libdrm -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/include/gtk-3.0/unix-print -I/usr/include/at-spi2-atk/2.0 -I/usr/include/gdkmm-3.0 -I/usr/include/cairomm-1.0 -I/usr/lib/gdkmm-3.0/include -I/usr/lib/gtkmm-3.0/include -I/usr/lib/glib-2.0/include -I/usr/lib/libffi-3.2.1/include -I/usr/lib/glibmm-2.4/include -I/usr/lib/sigc++-2.0/include -I/usr/lib/giomm-2.4/include -I/usr/lib/pangomm-1.4/include -I/usr/lib/cairomm-1.0/include -I/usr/lib/dbus-1.0/include -I/usr/include/c++ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Settings.o src/Settings.cpp

${OBJECTDIR}/src/WiFiSettings.o: src/WiFiSettings.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/gtkmm-3.0 -I/usr/include/atkmm-1.6 -I/usr/include/atk-1.0 -I/usr/include/glib-2.0 -I/usr/include/glibmm-2.4 -I/usr/include/sigc++-2.0 -I/usr/include/giomm-2.4 -I/usr/include/blkid -I/usr/include/uuid -I/usr/include/pangomm-1.4 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/gtk-3.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/libdrm -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/include/gtk-3.0/unix-print -I/usr/include/at-spi2-atk/2.0 -I/usr/include/gdkmm-3.0 -I/usr/include/cairomm-1.0 -I/usr/lib/gdkmm-3.0/include -I/usr/lib/gtkmm-3.0/include -I/usr/lib/glib-2.0/include -I/usr/lib/libffi-3.2.1/include -I/usr/lib/glibmm-2.4/include -I/usr/lib/sigc++-2.0/include -I/usr/lib/giomm-2.4/include -I/usr/lib/pangomm-1.4/include -I/usr/lib/cairomm-1.0/include -I/usr/lib/dbus-1.0/include -I/usr/include/c++ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/WiFiSettings.o src/WiFiSettings.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -s -I/usr/include/gtkmm-3.0 -I/usr/include/atkmm-1.6 -I/usr/include/atk-1.0 -I/usr/include/glib-2.0 -I/usr/include/glibmm-2.4 -I/usr/include/sigc++-2.0 -I/usr/include/giomm-2.4 -I/usr/include/blkid -I/usr/include/uuid -I/usr/include/pangomm-1.4 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/gtk-3.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gio-unix-2.0 -I/usr/include/libdrm -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/include/gtk-3.0/unix-print -I/usr/include/at-spi2-atk/2.0 -I/usr/include/gdkmm-3.0 -I/usr/include/cairomm-1.0 -I/usr/lib/gdkmm-3.0/include -I/usr/lib/gtkmm-3.0/include -I/usr/lib/glib-2.0/include -I/usr/lib/libffi-3.2.1/include -I/usr/lib/glibmm-2.4/include -I/usr/lib/sigc++-2.0/include -I/usr/lib/giomm-2.4/include -I/usr/lib/pangomm-1.4/include -I/usr/lib/cairomm-1.0/include -I/usr/lib/dbus-1.0/include -I/usr/include/c++ -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
