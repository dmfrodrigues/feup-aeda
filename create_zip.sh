make clean
rm -rf documentacao/
doxygen doxygen.config
pdflatex apresentacao.tex
pdflatex apresentacao.tex
rm -f apresentacao.aux
rm -f apresentacao.log
rm -f apresentacao.nav
rm -f apresentacao.out
rm -f apresentacao.snm
rm -f apresentacao.toc
rm -f AEDA1920_Turma5_G3.zip
zip AEDA1920_Turma5_G3.zip codigo/ documentacao/ apresentacao.pdf README.md
