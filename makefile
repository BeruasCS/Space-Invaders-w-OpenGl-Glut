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
LDFLAGS = -L. -lfreeglut -lopengl32 -lglu32 -lmingw32

# Arquivos
SOURCES = $(wildcard $(SDIR)/*.cpp)
DEPS = $(wildcard $(IDIR)/*.h)
OBJECTS = $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SOURCES))

# Executavel
TARGET = $(BINDIR)/space_invaders.exe

# Regras

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@if not exist $(BINDIR) mkdir $(BINDIR)
	$(CXX) -o $(TARGET) $^ $(LDFLAGS)
	@echo Build Sucesso! Execute: $(TARGET)

# Regra de compilacao dos objetos
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	@if not exist $(ODIR) mkdir $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@if exist $(ODIR) rmdir /s /q $(ODIR)
	@if exist $(BINDIR) rmdir /s /q $(BINDIR)
	@echo Limpeza concluida.