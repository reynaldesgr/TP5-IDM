CXX = g++
CXXFLAGS = -I methods/ utils/ -I Random/include
LDFLAGS = -L Random/lib -lCLHEP-Random-2.1.0.0 -static

OBJ_DIR = obj

$(shell mkdir -p $(OBJ_DIR)/methods $(OBJ_DIR)/utils $(OBJ_DIR)/Random/include)

SOURCES_TP5A = tp5a.cpp methods/MonteCarlo.cpp utils/RandomMT.cpp
SOURCES_TP5B = tp5b.cpp methods/MonteCarlo.cpp

OBJECTS_TP5A = $(addprefix $(OBJ_DIR)/, $(SOURCES_TP5A:.cpp=.o))
OBJECTS_TP5B = $(addprefix $(OBJ_DIR)/, $(SOURCES_TP5B:.cpp=.o))

EXEC_TP5A = tp5a
EXEC_TP5B = tp5b

$(EXEC_TP5A): $(OBJECTS_TP5A)
	$(CXX) $(OBJECTS_TP5A) -o $(EXEC_TP5A) $(LDFLAGS)

$(EXEC_TP5B): $(OBJECTS_TP5B)
	$(CXX) $(OBJECTS_TP5B) -o $(EXEC_TP5B) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	$(shell mkdir -p $(dir $@)) 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC_TP5A) $(EXEC_TP5B)
