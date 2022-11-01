
CC=gcc
CPPFLAGS=`pkg-config --cflags gtk+-3.0`
CPPLIBS=`pkg-config --libs gtk+-3.0`
OUTPUT_NAME=netfx3
INCLUDE_DIR=include
SRC_DIR=src
OPTS=-rdynamic -g

######

RESOURCE_FILE=resources.c
ASSETS_DIR=assets
RESOURCE_=.gresources.xml

$(OUTPUT_NAME): $(RESOURCE_FILE)
	rm -rf bin
	mkdir bin
	$(CC) $(SRC_DIR)/* -o bin/$(OUTPUT_NAME) $(OPTS) -I $(INCLUDE_DIR) $(CPPFLAGS) $(CPPLIBS)



$(RESOURCE_FILE):
	##if [ -e src/$(RESOURCE_FILE) ]; then
	#	rm -f src/$(RESOURCE_FILE)
	#fi 

	glib-compile-resources --generate-source --sourcedir=$(ASSETS_DIR) --target=src/$(RESOURCE_FILE) $(RESOURCE_)
