all: vivek-jbt.pdf

vivek-jbt.pdf: main.tex
	pdflatex --shell-escape main.tex
	bibtex main
	pdflatex --shell-escape main
	pdflatex --shell-escape main

clean:
	rm -f vivek-jbt.pdf
	rm -f *.out *.bcf *.aux *.xwm *.log *.snm *.nav
	rm -rf _markdown_main/