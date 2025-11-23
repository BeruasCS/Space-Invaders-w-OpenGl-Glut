# Compilador
CXX = g++

# Flags:
# -I.  -> Procura headers (.h) na pasta atual (para achar GL/glut.h)
CXXFLAGS = -g -Wall -std=c++11 -I.

# Diretorios
IDIR = .
SDIR = .
ODIR = obj
BINDIR = bin

# Flags de Linkagem:
# -L.          -> Procura bibliotecas (.a) na pasta atual
# -lfreeglut   -> Linka com libfreeglut.a (que colocamos na pasta)
# -lopengl32... -> Bibliotecas padrao do Windows
LDFLAGS = -lGL -lGLU -lglut # <--- MODIFICADO para Linux/Unix

# Arquivos
SOURCES = $(wildcard $(SDIR)/*.cpp) $(SDIR)/TextureLoader.cpp # <--- MODIFICADO
DEPS = $(wildcard $(IDIR)/*.h)
OBJECTS = $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SOURCES))

# Executavel
TARGET = $(BINDIR)/space_invaders # <--- MODIFICADO (removido .exe)

# Regras

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR) # <--- MODIFICADO
	$(CXX) -o $(TARGET) $^ $(LDFLAGS)
	@echo Build Sucesso! Execute: $(TARGET)

# Regra de compilacao dos objetos
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	mkdir -p $(ODIR) # <--- MODIFICADO
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(ODIR) # <--- MODIFICADO
	rm -rf $(BINDIR) # <--- MODIFICADO
	@echo Limpeza concluida.
