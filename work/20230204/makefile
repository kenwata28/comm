#
# comment
#   cmp prompt つかえないので、powershell -Command "" に頼る
#

TARGET = TypeRunnyar

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cc=.o)))


$(TARGET): $(OBJS) $(LIBS)	
	g++ -o $@ $^ -s -lcomctl32 -Wl,--subsystem,windows

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	powershell -Command "if (-not (TEST-PATH $(OBJ_DIR))) { mkdir $(OBJ_DIR) }"
	g++ -D UNICODE -D _UNICODE -I$(INC_DIR) -c $< -o $@ 

all: clean $(TARGET)

clean:
	powershell -Command "rm -R $(TARGET).exe"
	powershell -Command "rm -R $(OBJS)"

#
#



