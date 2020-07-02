LATEX=latexmk -f -synctex=1 -interaction=nonstopmode -pdf
# -outdir=%OUTDIR% %DOC%

OUTFILES=apresentacao/AEDA_proj_pres1.pdf \
		 apresentacao/AEDA_proj_pres2.pdf

all: $(OUTFILES)

%.pdf: %.tex
	cd $(<D) && $(LATEX) $(<F)
