
CFLAGS=$(shell pkg-config --cflags gtk+-3.0) -DGDK_WINDOWING_X11
LDFLAGS=$(shell pkg-config --libs gtk+-3.0)

app: main.c
	gcc $(CFLAGS) -o app $< $(LDFLAGS)

clean:
	rm -f app

