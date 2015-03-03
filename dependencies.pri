# This file sets up the dependencies for libraries that are built with
# this project. Specify the libraries you need to depend on in the variable
# DEPENDENCY_LIBRARIES and this will add them to the linker command line.

win32: {
    EXT=lib
    PREFIX=
}
else:  {
    EXT=a
    PREFIX=lib
}


CONFIG(debug, debug|release) {
    BUILD_TYPE = debug
} else {
    BUILD_TYPE = release
}

DESTDIR = ..

for(dep, DEPENDENCY_LIBRARIES) {
    #message($$TARGET depends on $$dep ($${DESTDIR}/$${dep}/$${BUILD_TYPE}/$${PREFIX}$${dep}.$${EXT}))
    LIBS += $${DESTDIR}/$${dep}/$${BUILD_TYPE}/$${PREFIX}$${dep}.$${EXT}
    PRE_TARGETDEPS += $${DESTDIR}/$${dep}/$${BUILD_TYPE}/$${PREFIX}$${dep}.$${EXT}
}
