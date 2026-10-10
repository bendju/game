CXX = g++
CXXFLAGS = -Wall -std=c++17 -Idatas $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer
TARGET = program
BUILD_DIR = build

# Forrásfájlok
SOURCES = $(wildcard *.cpp) $(wildcard datas/*.cpp)
OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o)))

# Alapértelmezett cél
all: $(BUILD_DIR) $(TARGET)

# Build mappa létrehozása
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Linkelés (hozzáadjuk az LDFLAGS-t)
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Fordítás - főkönyvtár
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Fordítás - datas könyvtár
$(BUILD_DIR)/%.o: datas/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

info:
	@echo "SOURCES = $(SOURCES)"
	@echo "OBJECTS = $(OBJECTS)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
