%{
#include "TSingleton.h"
#include "TApplication.h"
%}

%template(AppSingleton) Tubras::TSingleton<TApplication>;
%include TApplication.h


