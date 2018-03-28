CC=g++
CFLAGS=
objects=Shader.o Camera.o Texture2D.o RenderTexture.o Model.o first.o glad.o stb_image.o
headers=Shader.h Model.h Camera.h Texture2D.h RenderTexture.h
gl_libs=-lGL -lglfw
exe_libs=-lX11 -lpthread -ldl


first: $(objects)
	$(CC) $(CFLAGS) $(gl_libs) $(exe_libs) $(objects) -o first

glad.o: glad.c
	$(CC) $(CFLAGS) -c glad.c

stb_image.o: stb_image.cpp
	$(CC) $(CFLAGS) -c stb_image.cpp

Shader.o: Shader.cpp Shader.h
	$(CC) $(CFLAGS) $(gl_libs) -c Shader.cpp

Camera.o: Camera.cpp Camera.h
	$(CC) $(CFLAGS) $(gl_libs) -c Camera.cpp

Texture2D.o: Texture2D.cpp Texture2D.h
	$(CC) $(CFLAGS) $(gl_libs) -c Texture2D.cpp

RenderTexture.o: RenderTexture.cpp RenderTexture.h
	$(CC) $(CFLAGS) $(gl_libs) -c RenderTexture.cpp

Model.o: Model.cpp Model.h
	$(CC) $(CFLAGS) $(gl_libs) -c Model.cpp

first.o: first.cpp $(headers)
	$(CC) $(CFLAGS) $(gl_libs) -c first.cpp

clean:
	rm *.o first
