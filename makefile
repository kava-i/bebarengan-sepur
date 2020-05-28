all:
	mkdir -p build
	cd build && pdflatex ../bebarengan.tex && biber bebarengan % && pdflatex ../bebarengan.tex
