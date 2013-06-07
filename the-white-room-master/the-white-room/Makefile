linux:
	@echo ""
	#g++ -I. *.cpp objects/*.cpp gameStates/*.cpp events/*.cpp libglfw.a -lX11 -lGL -lGLU -lrt -lm -lXrandr -pthread -DGL_GLEXT_PROTOTYPES -o The-White-Room
	@echo ""
	g++ -I. *.cpp objects/*.cpp objects/mainMenu/*.cpp objects/credits/*.cpp gameStates/*.cpp events/*.cpp audio/*.cpp $< audio/FMOD/api/lib/libfmodex64.so  libglfw.a -lX11 -lGL -lGLU -lGLEW -lrt -lm -lXrandr -lfreetype -pthread -DGL_GLEXT_PROTOTYPES -o The-White-Room

glfw:
	(cd glfw-2.7.7 && make x11 && cp lib/x11/libglfw* ..)


#	g++ Main.cpp GLSL_helper.cpp MStackHelp.cpp GeometryCreator.cpp -DGL_GLEXT_PROTOTYPES -lGL -lGLU -lglut -o GeomDemo

clean:
	rm -f *~
	rm -f GeomDemo
	rm -f *.o
