all:
	mkdir -p build
	cd build && pdflatex ../main.tex && bibtex main.aux && pdflatex ../main.tex
