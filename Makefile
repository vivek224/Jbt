all: vivek-jbt.pdf

vivek-jbt.pdf: main.tex
	sudo pdflatex main.tex
	sudo bibtex main
	sudo pdflatex main
	sudo pdflatex main

clean:
	sudo rm -f vivek-jbt.pdf
	rm *.out *.bcf *.aux *.xwm
