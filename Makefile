
CC=gcc
CPPFLAGS=`pkg-config --cflags gtk+-3.0`
CPPLIBS=`pkg-config --libs gtk+-3.0`
OUTPUT_NAME=netfx3
INCLUDE_DIR=include
SRC_DIR=src
OPTS=-g

######

RESOURCE_FILE=resources.c
ASSETS_DIR=assets
RESOURCE_=.gresources.xml

$(OUTPUT_NAME): $(RESOURCE_FILE)
	rm -rf bin
	mkdir bin
	$(CC) $(SRC_DIR)/*.c -c $(OPTS) -I $(INCLUDE_DIR) $(CPPFLAGS)
	$(CC) *.o -o bin/$(OUTPUT_NAME) $(CPPLIBS)

	rm -f *.o


$(RESOURCE_FILE):
	
	glib-compile-resources --generate-source --sourcedir=$(ASSETS_DIR) --target=src/$(RESOURCE_FILE) $(RESOURCE_) --dependency-file=rdependencies.txt

	windres -i $(SRC_DIR)/resource.rc -o resource.o --output-format=coff --input-format=rc