pushd %tubras%\src\swig
swig -c++ -python -o tubras_wrap.cpp -Ic:\gdev\tubras\include tubras.i
popd

