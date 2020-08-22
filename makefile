TARGET = a.out
SOURCE = $(wildcard *.cpp)
OBJECT = $(patsubst %.cpp, %.o, $(SOURCE))
#CFlags = -lpthread
REMOVE := rm -rf
CC := g++
#$^ 为所有依赖文件 $@ 为所有目标文件 $< 为依赖文件的第一个文件

$(TARGET) : $(OBJECT)
	$(CC) $^ -o $@
	#$(CC) -o $^ $@ $(CFlags)
$(OBJECT) : $(SOURCE)

.PHONY :
clear :
	$(REMOVE) $(OBJECT) $(TARGET)
