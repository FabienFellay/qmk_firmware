#!/usr/bin/env bash

# Script to generate the PDF documentation from markdown source via Pandoc

# Exit script on first error
set -o errexit

# Make the script work independently of where it has been invoked from
source_path=$(dirname "${BASH_SOURCE[0]}")
echo -e "\n--> Move to $source_path"
cd "$source_path"

# Documentation filename
docname=keychron_q6_custom_iso_encoder_keychron

# Process script options
convert=true
clean=true

for i in $@
do
    if [[ "$i" == "--no_convert" ]]
    then
        convert=false
    elif [[ "$i" == "--no_clean" ]]
    then
        clean=false
    else
        echo -e "\nUnknown option: $i. Process stopped without any action."
        exit 1
    fi
done

# Convert all SVG images to PDF with Inkscape (rsvg-convert is not satisfying)
if [[ $convert == true ]]
then
    echo -e "\n--> Converting SVG images to PDF with Inkscape CLI ...\n"

    find . \
        -name *.svg \
        -exec bash -c 'echo "Convert file ${1}/${2:2}"' \
        - "$source_path" '{}' \; \
        -exec inkscape --export-type="pdf" {} \;
fi

# Generate PDF documentation
echo -e "\n--> Generating PDF documentation via Pandoc ..."

# Add option --verbose for more information during PDF generation
pandoc ./$docname.md \
    --from markdown-implicit_figures \
    --variable=geometry:a4paper \
    --variable=geometry:top=1.0cm \
    --variable=geometry:bottom=1.8cm \
    --variable=geometry:left=2.5cm \
    --variable=geometry:right=2.5cm \
    --variable=fontfamily:dejavu \
    --variable=fontsize:11pt \
    --variable=colorlinks:true \
    --variable=linkcolor:SlateBlue \
    --variable=filecolor:Sienna \
    --variable=citecolor:Teal \
    --variable=urlcolor:RoyalBlue \
    --variable=toccolor:MidnightBlue \
    --variable=urlstyle:sf \
    --variable=linestretch:1.25 \
    --variable=secnumdepth:3 \
    --number-sections \
    --include-in-header=./config/head.tex \
    --variable=hyperrefoptions:bookmarksnumbered \
    --pdf-engine=pdflatex \
    --lua-filter=./config/line_breaks.lua \
    --metadata-file=./config/metadata.yaml \
    --toc=true \
    --output ./$docname.pdf

echo -e "\n--> PDF documentation now generated"

# Clean all PDF images previously generated with Inkscape
if [[ $clean == true ]]
then
    echo -e "\n--> Cleaning Inkscape-generated PDF images ...\n"

    find . \
        -name *.svg \
        -exec bash -c 'f="${1}/${2:2}" ; echo "Clean file ${f%.svg}".pdf' \
        - "$source_path" '{}' \; \
        -exec bash -c 'rm "${1%.svg}".pdf' - '{}' \;
fi

# Copy the generated PDF to the repository root folder
root_folder=$(git rev-parse --show-toplevel)
cp -p ./$docname.pdf "$root_folder"

echo -e "\n--> PDF documentation copied to the repository root folder"
