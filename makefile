IFLAGS =-I$(IDIR)
LFLAGS =-L$(LDIR) -lapp

CC     =g++

SDIR   =./src
IDIR   =./include
ODIR   =./obj
LDIR   =./lib
TDIR   =./tests
BDIR   =./bin

CFLAGS =-std=c++11 -O3

all: $(BDIR)/main.app

makefolders:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)
	mkdir -p $(BDIR)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -c $(IFLAGS) $< -o $@

makelib: makefolders $(LDIR)/libapp.a

$(LDIR)/libapp.a:           $(ODIR)/main.o $(ODIR)/address.o $(ODIR)/Cargo.o $(ODIR)/currency.o $(ODIR)/person.o $(ODIR)/phonenumber.o $(ODIR)/service.o $(ODIR)/Time.o $(ODIR)/truck.o $(ODIR)/utils.o $(ODIR)/vat.o
	rm -f $(LDIR)/libapp.a
	ar rvs $(LDIR)/libapp.a $(ODIR)/main.o $(ODIR)/address.o $(ODIR)/Cargo.o $(ODIR)/currency.o $(ODIR)/person.o $(ODIR)/phonenumber.o $(ODIR)/service.o $(ODIR)/Time.o $(ODIR)/truck.o $(ODIR)/utils.o $(ODIR)/vat.o

test: makelib
	g++ $(TDIR)/alltests.cpp $(IFLAGS) -o $(TDIR)/tests.app $(LFLAGS)
	$(TDIR)/tests.app

$(BDIR)/main.app: makelib               $(ODIR)/main.o
	$(CC) $(CFLAGS) -o $(BDIR)/main.app $(ODIR)/main.o $(LFLAGS)

clean:
	rm -rf $(ODIR)
	rm -rf $(LDIR)
	rm -rf $(TDIR)/*.o $(TDIR)/*.app
	rm -rf $(BDIR)
