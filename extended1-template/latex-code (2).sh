#!/usr/bin/env bash

set -ex

function make_latex {
	author=$1
	cat <<'EOF'
\documentclass[a4paper]{article}

\usepackage[a4paper, total={18cm, 26cm}]{geometry}
\usepackage[T1]{fontenc} % needed by beramono
\usepackage{textcomp}
% beramono.sty and MnSymbol.sty come with texlive-fonts-extra in Debian
\usepackage[scaled=0.85]{beramono} % tt font supporting slshape and zero with dot
\usepackage{MnSymbol} % fancy symbols for line-breaks
\usepackage[utf8]{inputenc}
\usepackage{listingsutf8}  % code listings, comes with texlive-latex-recommended
%\usepackage{listings}
\usepackage{xcolor}
\usepackage{verbatim}
\usepackage{graphicx} % \includegraphics[width=\textwidth]{image.png}

\protected\def\plusminus{\ensuremath{\pm}}
\DeclareUnicodeCharacter{C2B1}{\plusminus}

\lstset{
  inputencoding=utf8,
  literate={±}{\plusminus}1
}

\lstdefinestyle{bwC++}{
  language=C++,morekeywords={concept,consteval,constinit,constexpr,co_await,co_return,co_yield,requires},
  basicstyle=\ttfamily,
  keywordstyle=\bfseries,
  stringstyle=\slshape,
  commentstyle=\slshape,
  morecomment=[s][\bfseries\slshape]{/**}{*/},
  tabsize=4,
  showstringspaces=false,
  breaklines=true, breakatwhitespace=true,
  prebreak={\hbox{\quad$\rhookswarrow$}},
  postbreak={\hbox{$\lhookrightarrow$}},
  breakindent={-8pt}, breakautoindent=false,
  numbers=left, numberstyle=\tiny,
  frameshape={RYR}{N}{N}{YYY} %frame=tb,frameround=tttt
}

\lstdefinestyle{colorC++}{
  language=C++,morekeywords={concept,consteval,constinit,constexpr,co_await,co_return,co_yield,requires},
  basicstyle=\ttfamily,
  keywordstyle=\textcolor{blue},
  stringstyle=\slshape\textcolor{red!70!black},
  commentstyle=\slshape\textcolor{green!50!black},
  morecomment=[s][\bfseries\slshape\textcolor{green!50!black}]{/**}{*/},
  tabsize=4,
  showstringspaces=false,
  breaklines=true, breakatwhitespace=true,
  prebreak={\hbox{\quad\textcolor{red}{$\rhookswarrow$}}},
  postbreak={\hbox{\textcolor{red}{$\lhookrightarrow$}}},
  breakindent={-8pt}, breakautoindent=false,
  numbers=left, numberstyle=\tiny,
  frameshape={RYR}{N}{N}{YYY} %frame=tb,frameround=tttt
}

\lstdefinestyle{colorBash}{
  language=bash,
  basicstyle=\ttfamily,
  keywordstyle=\textcolor{blue},
  stringstyle=\slshape\textcolor{red!70!black},
  commentstyle=\slshape\textcolor{green!50!black},
  morecomment=[s][\bfseries\slshape\textcolor{green!50!black}]{/**}{*/},
  tabsize=4,
  showstringspaces=false,
  breaklines=true, breakatwhitespace=true,
  prebreak={\hbox{\quad\textcolor{red}{$\rhookswarrow$}}},
  postbreak={\hbox{\textcolor{red}{$\lhookrightarrow$}}},
  breakindent={-8pt}, breakautoindent=false,
  numbers=left, numberstyle=\tiny,
  frameshape={RYR}{N}{N}{YYY} %frame=tb,frameround=tttt
}

EOF
	echo '\title{'$title'}'
	echo '\author{'$author'}'
	echo '\begin{document}'
	echo '  \maketitle'

	tex_files=$(find . -type f -iname "*.tex")
	for f in $tex_files ; do
		filename=$(basename $f)
		case "$filename" in
			"listing.tex")
				continue
				;;
		esac
		echo '  \input{'$f'}'
	done

	python_files=$(find . -type f -iname "*.py")
	header_files=$(find . -type f \( -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp" \))
	source_files=$(find . -type f \( -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" \))
	for f in $python_files $header_files $source_files; do
		dirname=${f#./}
		dirname=${dirname%%/*}
		case "$dirname" in
			.idea|"cmake-build-"*|"build"|"out")
				continue
				;;
		esac
		filename=$(basename $f)
		case "$filename" in
			"doctest.h")
				continue
				;;
		esac
		name=$(echo "$f" | sed -e 's/_/\\_/g')
		echo '  \lstinputlisting[style=colorC++,caption={'$name'}]{'$f'}'
	done
	text_files=$(find . -type f \( -iname "*.txt" -o -iname "*.md" \))
	for f in $text_files ; do
		dirname=${f#./}
		dirname=${dirname%%/*}
		case "$dirname" in
			.idea|"cmake-build-"*|"build"|"out")
				continue
				;;
		esac
		filename=$(basename $f)
		name=$(echo "$f" | sed -e 's/_/\\_/g')
		echo '  \lstinputlisting[style=colorBash,caption={'$name'}]{'$f'}'
	done
	echo '\end{document}'
}

author="$1"
title="$2"
if [ -z "$author" ]; then
	echo -n "Enter the name of the author: "
	read author
fi

if [ -z "$title" ]; then
	echo -n "Enter the title: "
	read title
fi

echo "Generates LaTeX report from C/C++ sources and TeX files it can find in the current directory."
echo "Assumes that pdflatex (from TeX Live) is installed."
echo -e "Usage:\n\t$0 \"Author Name\" \"Document Title\""
make_latex "$author" "$title" > listing.tex
pdflatex listing.tex && pdflatex listing.tex && okular listing.pdf
