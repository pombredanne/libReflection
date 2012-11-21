ACLOCAL_AMFLAGS=-I build-aux
AM_CXXFLAGS=-I "${srcdir}/include" -std=c++11 ${BOOST_CPPFLAGS}

lib_LTLIBRARIES=libReflection.la
libReflection_la_SOURCES=src/Type.cpp src/Function.cpp src/StackTrace.cpp
libReflection_la_LIBADD=-ldw

include_HEADERS=include/Reflection.hpp
include_Reflectiondir=$(includedir)/Reflection
include_Reflection_HEADERS= \
	include/Reflection/Class.hpp include/Reflection/Function.hpp \
	include/Reflection/Main.hpp include/Reflection/Namespace.hpp \
	include/Reflection/StackTrace.hpp include/Reflection/Template.hpp \
	include/Reflection/Type.hpp
