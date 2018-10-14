all: vivek-jbt.pdf

vivek-jbt.pdf: main.tex
	pdflatex --shell-escape main.tex
	bibtex main
	pdflatex main
	pdflatex main

clean:
	sudo rm -f vivek-jbt.pdf
	rm *.out *.bcf *.aux *.xwm
