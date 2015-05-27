#!/bin/bash
set -e
echo "This will remove the following files:"
ls *.idx *.log *.scn *.toc
echo -n "Delete these files? (Y/N): "
read answer 
if [[ "$answer" == "Y" ]]; then 
	rm *.idx *.log *.scn *toc
else 
	exit 0
fi
