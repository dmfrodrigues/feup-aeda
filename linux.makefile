IFLAGS =-I$(IDIR)

CC     =g++

SDIR   =./src
IDIR   =./include
ODIR   =./obj
BDIR   =./bin

CFLAGS =-std=c++11 -O3 $(IFLAGS)

all: makefolders $(BDIR)/main.app

makefolders:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)
	mkdir -p $(BDIR)

$(BDIR)/main.app: $(ODIR)/FractalBitmap.o $(ODIR)/CURSOR_CROSS.o $(ODIR)/FractalFrame.o $(ODIR)/FractalPanel.o $(ODIR)/InfoPanel.o $(ODIR)/HDPrintscreenDialog.o
	rm -f $(LDIR)/libfractalapp.a
	ar rvs $(LDIR)/libfractalapp.a $(ODIR)/FractalBitmap.o $(ODIR)/CURSOR_CROSS.o $(ODIR)/FractalFrame.o $(ODIR)/FractalPanel.o $(ODIR)/InfoPanel.o $(ODIR)/HDPrintscreenDialog.o

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) $^ -o $@
