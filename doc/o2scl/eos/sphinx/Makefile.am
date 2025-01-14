help:
	@echo "This the O2scl makefile for the doc/o2scl/sphinx subdirectory."
	@echo
	@echo "The traditional GNU-style targets apply. In addition there"
	@echo "are a couple extra targets which may be useful listed below."
	@echo 
	@echo "Additional package-specific targets"
	@echo "-------------------------------------------------------------"
	@echo "help:                 Show this help file"
	@echo 
	@echo "Developer targets"
	@echo "-------------------------------------------------------------"
	@echo 

docdir = $(prefix)/share/doc/o2scl/eos
docclassdir = $(prefix)/share/doc/o2scl/eos/class
docfunctiondir = $(prefix)/share/doc/o2scl/eos/function
dochtmldir = $(prefix)/share/doc/o2scl/eos/html
dochtmlclassdir = $(prefix)/share/doc/o2scl/eos/html/class

dochtmlstaticdir = $(prefix)/share/doc/o2scl/eos/html/_static
dochtmlsourcesdir = $(prefix)/share/doc/o2scl/eos/html/_sources
dochtmlsourcesclassdir = $(prefix)/share/doc/o2scl/eos/html/_sources/class
dochtmlimagesdir = $(prefix)/share/doc/o2scl/eos/html/_images

# These are the files installed by 'make install'
dist_doc_DATA = *.rst
dist_docclass_DATA = *.rst
dist_docfunction_DATA = *.rst
dist_dochtml_DATA = ../../eos/html/*.html ../../eos/html/*.js ../../eos/html/*.inv
dist_dochtmlclass_DATA = ../../eos/html/class/*.html

dist_dochtmlstatic_DATA = ../../eos/html/_static/*
dist_dochtmlimages_DATA = ../../eos/html/_images/*
dist_dochtmlsources_DATA = ../../eos/html/_sources/*.txt
dist_dochtmlsourcesclass_DATA = ../../eos/html/_sources/class/*.txt

# These are the additional files included in the distribution
# 
# AWS 5/22/2020: I think all of the files listed for the make install
# target above are already included so all we need are the 'extra'
# files
EXTRA_DIST = conf.py class_list

SUBDIRS = 

emacs-clean:
	rm -f *~
	rm -f */*~
	rm -f */*/*~
	rm -f */*/*/*~
	rm -f */*/*/*/*~

SPHINXOPTS    =
SPHINXBUILD   = sphinx-build
SPHINXPROJ    = o2scl_eos
SOURCEDIR     = .
BUILDDIR      = build

sphinx-help:
	sphinx-build --help

html: Makefile
	sphinx-build -v -b html "." ../../eos/html 2>&1 | tee sphinx.log

html-nit: Makefile
	sphinx-build -v -n -b html "." ../../eos/html

full-html:
	sphinx-build -v -a -E -b html "." ../../eos/html

rst-files: empty
	grep "kind=\"class\"" ../xml/index.xml | grep -v "::slice" \
		> class_list
	cp ref_header ref.rst
	btmanip -parse ../../../../data/o2scl/o2scl_eos.bib -rst temp.rst
	cat temp.rst >> ref.rst
	rm -f temp.rst
	g++ -o ../../make_rst ../../make_rst.cpp
	rm -f class/*.rst
	../../make_rst eos | tee make_rst.out

o2scl-doc: rst-files html

empty:
