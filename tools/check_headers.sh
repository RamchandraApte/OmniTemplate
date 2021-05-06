limit_jobs(){
	while [[ $(jobs -p | wc -l) >= $(nproc) ]]; do wait -n; done
}
# Checks every header can be compiled individually. Useful for checking all necessary includes are present.
GLOBIGNORE='src/core/*'
for file in src/**/*.hpp; do g++-8 -Isrc -std=c++17 -fsyntax-only $file & limit_jobs; done
