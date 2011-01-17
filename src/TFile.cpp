//-----------------------------------------------------------------------------
// This is free and unencumbered software released into the public domain.
// For the full text of the Unlicense, see the file "docs/unlicense.html".
// Additional Unlicense information may be found at http://unlicense.org.
//-----------------------------------------------------------------------------
#include "tubras.h"

#ifdef TUBRAS_PLATFORM_WINDOWS
	#if !defined ( _WIN32_WCE )
		#include <direct.h> // for _chdir
	#endif
#define SEPARATOR '\\'
#else
	#include <unistd.h>
	#include <limits.h>
	#include <stdlib.h>
    #include <dirent.h>
    #include <utime.h>
    #include <fcntl.h>
    #define _chdir chdir
#define SEPARATOR '/'
#endif
#include <errno.h>
#include <stdio.h>

namespace Tubras
{


    ////////////////////////////////////////////////////////////////////
    //     Function: ExecutionEnvironment::get_environment_variable
    //       Access: Public, Static
    //  Description: Returns the definition of the indicated environment
    //               variable, or the empty TStdString if the variable is
    //               undefined.  The nonstatic implementation.
    ////////////////////////////////////////////////////////////////////
    TStdString TExecutionEnvironment::get_environment_variable(const TStdString &var) 
    {
        const char *def = getenv(var.c_str());
        if (def != (char *)NULL) {
            return def;
        }
        return TStdString();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: ExecutionEnviroment::expand_string
    //       Access: Public, Static
    //  Description: Reads the TStdString, looking for environment variable
    //               names marked by a $.  Expands all such variable
    //               names.  A repeated dollar sign ($$) is mapped to a
    //               single dollar sign.
    //
    //               Returns the expanded TStdString.
    ////////////////////////////////////////////////////////////////////
    TStdString TExecutionEnvironment::expand_string(const TStdString &str) 
    {
        TStdString result;

        size_t last = 0;
        size_t dollar = str.find('$');
        while (dollar != TStdString::npos && dollar + 1 < str.length()) {
            size_t start = dollar + 1;

            if (str[start] == '$') {
                // A double dollar sign maps to a single dollar sign.
                result += str.substr(last, start - last);
                last = start + 1;

            } else {
                TStdString varname;
                size_t end = start;

                if (str[start] == '{') {
                    // Curly braces delimit the variable name explicitly.
                    end = str.find('}', start + 1);
                    if (end != TStdString::npos) {
                        varname = str.substr(start + 1, end - (start + 1));
                        end++;
                    }
                }

                if (end == start) {
                    // Scan for the end of the variable name.
                    while (end < str.length() && (isalnum(str[end]) || str[end] == '_')) {
                        end++;
                    }
                    varname = str.substr(start, end - start);
                }

                TStdString subst =
                    result += str.substr(last, dollar - last);
                result += get_environment_variable(varname);
                last = end;
            }

            dollar = str.find('$', last);
        }

        result += str.substr(last);

        return result;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: ExecutionEnviroment::get_cwd
    //       Access: Public, Static
    //  Description: Returns the name of the current working directory.
    ////////////////////////////////////////////////////////////////////
    TFile TExecutionEnvironment::get_cwd() 
    {
        // getcwd() requires us to allocate a dynamic buffer and grow it on
        // demand.
        static size_t bufsize = 1024;
        static char *buffer = NULL;

        if (buffer == (char *)NULL) {
            buffer = new char[bufsize];
        }

#ifdef WIN32
        while (_getcwd(buffer,(int) bufsize) == (char *)NULL) {
#else
        while (getcwd(buffer,(int) bufsize) == (char *)NULL) {
#endif
            if (errno != ERANGE) {
                perror("getcwd");
                return TStdString();
            }
            delete[] buffer;
            bufsize = bufsize * 2;
            buffer = new char[bufsize];
            assert(buffer != (char *)NULL);
        }

        return TFile::from_os_specific(buffer);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::TResults::Constructor
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    TSearchPath::TResults::
        TResults() {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::TResults::Copy Constructor
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    TSearchPath::TResults::
        TResults(const TSearchPath::TResults &copy) :
    _files(copy._files)
    {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::TResults::Copy Assignment Operator
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::TResults::
        operator = (const TSearchPath::TResults &copy) {
            _files = copy._files;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::TResults::Destructor
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    TSearchPath::TResults::
        ~TResults() {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::TResults::clear
    //       Access: Public
    //  Description: Removes all the files from the list.
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::TResults::
        clear() {
            _files.clear();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::TResults::get_num_files
    //       Access: Public
    //  Description: Returns the number of files on the result list.
    ////////////////////////////////////////////////////////////////////
    int TSearchPath::TResults::
        get_num_files() const {
            return (int) _files.size();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::TResults::get_file
    //       Access: Public
    //  Description: Returns the nth file on the result list.
    ////////////////////////////////////////////////////////////////////
    const TFile &TSearchPath::TResults::
        get_file(int n) const {
            assert(n >= 0 && n < (int)_files.size());
            return _files[n];
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::TResults::add_file
    //       Access: Public
    //  Description: Adds a new file to the result list.
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::TResults::
        add_file(const TFile &file) {
            _files.push_back(file);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::Default Constructor
    //       Access: Public
    //  Description: Creates an empty search path.
    ////////////////////////////////////////////////////////////////////
    TSearchPath::
        TSearchPath() {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::Constructor
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    TSearchPath::
        TSearchPath(const TStdString &path, const TStdString &delimiters) {
            append_path(path, delimiters);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::Copy Constructor
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    TSearchPath::
        TSearchPath(const TSearchPath &copy) :
    _directories(copy._directories)
    {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::Copy Assignment Operator
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::
        operator = (const TSearchPath &copy) {
            _directories = copy._directories;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::Destructor
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    TSearchPath::
        ~TSearchPath() {
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::clear
    //       Access: Public
    //  Description: Removes all the directories from the search list.
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::
        clear() {
            _directories.clear();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::append_directory
    //       Access: Public
    //  Description: Adds a new directory to the end of the search list.
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::
        append_directory(const TFile &directory) {
            _directories.push_back(directory);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::prepend_directory
    //       Access: Public
    //  Description: Adds a new directory to the front of the search list.
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::
        prepend_directory(const TFile &directory) {
            _directories.insert(_directories.begin(), directory);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::append_path
    //       Access: Public
    //  Description: Adds all of the directories listed in the search path
    //               to the end of the search list.
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::
        append_path(const TStdString &path, const TStdString &delimiters) {
            size_t p = 0;
            while (p < path.length()) {
                size_t q = path.find_first_of(delimiters, p);
                if (q == TStdString::npos) {
                    _directories.push_back(path.substr(p));
                    return;
                }
                if (q != p) {
                    _directories.push_back(path.substr(p, q - p));
                }
                p = q + 1;
            }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::append_path
    //       Access: Public
    //  Description: Adds all of the directories listed in the search path
    //               to the end of the search list.
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::
        append_path(const TSearchPath &path) {
            copy(path._directories.begin(), path._directories.end(),
                back_inserter(_directories));
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::prepend_path
    //       Access: Public
    //  Description: Adds all of the directories listed in the search path
    //               to the beginning of the search list.
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::
        prepend_path(const TSearchPath &path) {
            if (!path._directories.empty()) {
                Directories new_directories = path._directories;
                copy(_directories.begin(), _directories.end(),
                    back_inserter(new_directories));
                _directories.swap(new_directories);
            }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::is_empty
    //       Access: Public
    //  Description: Returns true if the search list is empty, false
    //               otherwise.
    ////////////////////////////////////////////////////////////////////
    bool TSearchPath::
        is_empty() const {
            return _directories.empty();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::get_num_directories
    //       Access: Public
    //  Description: Returns the number of directories on the search list.
    ////////////////////////////////////////////////////////////////////
    int TSearchPath::
        get_num_directories() const {
            return (int)_directories.size();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::get_directory
    //       Access: Public
    //  Description: Returns the nth directory on the search list.
    ////////////////////////////////////////////////////////////////////
    const TFile &TSearchPath::
        get_directory(int n) const {
            assert(n >= 0 && n < (int)_directories.size());
            return _directories[n];
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::find_file
    //       Access: Public
    //  Description: Searches all the directories in the search list for
    //               the indicated file, in order.  Returns the full
    //               matching pathname of the first match if found, or the
    //               empty TStdString if not found.
    ////////////////////////////////////////////////////////////////////
    TFile TSearchPath::
        find_file(const TFile &filename) const {
            if (filename.is_local()) {
                Directories::const_iterator di;
                for (di = _directories.begin(); di != _directories.end(); ++di) {
                    TFile match((*di), filename);
                    if (match.exists()) {
                        if ((*di) == "." && filename.is_fully_qualified()) {
                            // A special case for the "." directory: to avoid prefixing
                            // an endless stream of ./ in front of files, if the
                            // filename already has a ./ prefixed
                            // (i.e. is_fully_qualified() is true), we don't
                            // prefix another one.
                            return filename;
                        } else {
                            return match;
                        }
                    }
                }
            }

            return TStdString();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::find_all_files
    //       Access: Public
    //  Description: Searches all the directories in the search list for
    //               the indicated file, in order.  Fills up the TResults
    //               list with *all* of the matching TFiles found, if
    //               any.  Returns the number of matches found.
    //
    //               It is the responsibility of the the caller to clear
    //               the TResults list first; otherwise, the newly-found
    //               files will be appended to the list.
    ////////////////////////////////////////////////////////////////////
    int TSearchPath::
        find_all_files(const TFile &filename,
        TSearchPath::TResults &results) const {
            int num_added = 0;

            if (filename.is_local()) {
                Directories::const_iterator di;
                for (di = _directories.begin(); di != _directories.end(); ++di) {
                    TFile match((*di), filename);
                    if (match.exists()) {
                        if ((*di) == "." && filename.is_fully_qualified()) {
                            // A special case for the "." directory: to avoid prefixing
                            // an endless stream of ./ in front of files, if the
                            // filename already has a ./ prefixed
                            // (i.e. is_fully_qualified() is true), we don't
                            // prefix another one.
                            results.add_file(filename);
                        } else {
                            results.add_file(match);
                        }
                        num_added++;
                    }
                }
            }

            return num_added;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::output
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::
        output(std::ostream &out, const TStdString &separator) const {
            if (!_directories.empty()) {
                Directories::const_iterator di = _directories.begin();
                out << (*di);
                ++di;
                while (di != _directories.end()) {
                    out << separator << (*di);
                    ++di;
                }
            }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TSearchPath::write
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    void TSearchPath::
        write(std::ostream &out, int indent_level) const {
            Directories::const_iterator di;
            for (di = _directories.begin(); di != _directories.end(); ++di) {
                for (int i = 0; i < indent_level; i++) {
                    out << ' ';
                }
                out << (*di) << "\n";
            }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: PPScope::expand_downcase
    //       Access: Private
    //  Description: Expands the "downcase" function variable.
    ////////////////////////////////////////////////////////////////////
    TStdString downcase(const TStdString &params) {
        TStdString result = params;
        TStdString::iterator si;
        for (si = result.begin(); si != result.end(); ++si) {
            (*si) = tolower(*si);
        }
        return result;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::Constructor
    //       Access: Public
    //  Description: This constructor composes the filename out of a
    //               directory part and a basename part.  It will insert
    //               an intervening '/' if necessary.
    ////////////////////////////////////////////////////////////////////
    TFile::
        TFile(const TFile &dirname, const TFile &basename) {
            if (dirname.empty()) {
                (*this) = basename;
            } else {
                TStdString dirpath = dirname.get_fullpath();
                if (dirpath[dirpath.length() - 1] == '/') {
                    (*this) = dirpath + basename.get_fullpath();
                } else {
                    (*this) = dirpath + "/" + basename.get_fullpath();
                }
            }
            _flags = 0;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::from_os_specific
    //       Access: Public, Static
    //  Description: This named constructor returns a Panda-style filename
    //               (that is, using forward slashes, and no drive letter)
    //               based on the supplied filename TStdString that describes
    //               a filename in the local system conventions (for
    //               instance, on Windows, it may use backslashes or begin
    //               with a drive letter and a colon).
    //
    //               Use this function to create a TFile from an
    //               externally-given filename TStdString.  Use
    //               to_os_specific() again later to reconvert it back to
    //               the local operating system's conventions.
    //
    //               This function will do the right thing even if the
    //               filename is partially local conventions and partially
    //               Panda conventions; e.g. some backslashes and some
    //               forward slashes.
    ////////////////////////////////////////////////////////////////////
    TFile TFile::
        from_os_specific(const TStdString &os_specific, TFile::Type type) {
#ifdef TUBRAS_PLATFORM_WINDOWS
            TStdString result = back_to_front_slash(os_specific);
            const TStdString &panda_root = get_tubras_root();

            // If the initial prefix is the same as panda_root, remove it.
            if (!panda_root.empty() && panda_root.length() < result.length()) {
                bool matches = true;
                size_t p;
                for (p = 0; p < panda_root.length() && matches; p++) {
                    char c = tolower(panda_root[p]);
                    if (c == '\\') {
                        c = '/';
                    }
                    matches = (c == tolower(result[p]));
                }

                if (matches) {
                    // The initial prefix matches!  Replace the initial bit with a
                    // leading slash.
                    result = result.substr(panda_root.length());
                    assert(!result.empty());
                    if (result[0] != '/') {
                        result = '/' + result;
                    }
                    TFile filename(result);
                    filename.set_type(type);
                    return filename;
                }
            }

            // All right, the initial prefix was not under panda_root.  But
            // maybe it begins with a drive letter.
            if (result.size() >= 3 && isalpha(result[0]) &&
                result[1] == ':' && result[2] == '/') {
                    result[1] = tolower(result[0]);
                    result[0] = '/';
            }

            TFile filename(result);
            filename.set_type(type);
            return filename;
#else  // WIN32
            // Generic Unix-style filenames--no conversion necessary.
            TFile filename(os_specific);
            filename.set_type(type);
            return filename;
#endif  // WIN32
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::expand_from
    //       Access: Public, Static
    //  Description: Returns the same thing as from_os_specific(), but
    //               embedded environment variable references
    //               (e.g. "$DMODELS/foo.txt") are expanded out.
    ////////////////////////////////////////////////////////////////////
    TFile TFile::
        expand_from(const TStdString &os_specific, TFile::Type type) {
            return from_os_specific(TExecutionEnvironment::expand_string(os_specific),
                type);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::temporary
    //       Access: Public
    //  Description: Generates a temporary filename within the indicated
    //               directory, using the indicated prefix.  If the
    //               directory is empty, a system-defined directory is
    //               chosen instead.
    //
    //               The generated filename did not exist when the
    //               TFile checked, but since it does not specifically
    //               create the file, it is possible that another process
    //               could simultaneously create a file by the same name.
    ////////////////////////////////////////////////////////////////////
    TFile TFile::
        temporary(const TStdString &dirname, const TStdString &prefix, Type type) {
            TStdString dname=dirname;

            if (dirname.empty()) {
                // If we are not given a dirname, use the system tempnam()
                // function to create a system-defined temporary filename.
#ifdef TUBRAS_PLATFORM_WINDOWS
                char *name = _tempnam(NULL, prefix.c_str());
                TFile result(name);
                free(name);
                result.set_type(type);
                return result;
#else                
                dname = "/tmp/";
#endif
            }

            // If we *are* given a dirname, then use our own algorithm to make
            // up a filename within that dirname.  We do that because the system
            // tempnam() (for instance, under Windows) may ignore the dirname.

            TFile result(dname, "");
            result.set_type(type);
            do {
                // We take the time of day and multiply it by the process time.
                // This will give us a very large number, of which we take the
                // bottom 24 bits and generate a 6-character hex code.
                int hash = (int)((clock() * time(NULL)) & 0xffffff);
                char hex_code[10];
                sprintf(hex_code, "%06x", hash);
                result.set_basename(prefix + hex_code);
            } while (result.exists());

            return result;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::set_fullpath
    //       Access: Public
    //  Description: Replaces the entire filename: directory, basename,
    //               extension.  This can also be achieved with the
    //               assignment operator.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        set_fullpath(const TStdString &s) {
            (*this) = s;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::set_dirname
    //       Access: Public
    //  Description: Replaces the directory part of the filename.  This is
    //               everything in the filename up to, but not including
    //               the rightmost slash.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        set_dirname(const TStdString &s) {
            if (s.empty()) {
                // Remove the directory prefix altogether.
                _filename.replace(0, _basename_start, "");

                int length_change = - ((int)_basename_start);

                _dirname_end = 0;
                _basename_start += length_change;
                _basename_end += length_change;
                _extension_start += length_change;

            } else {
                // Replace the existing directory prefix, or insert a new one.

                // We build the TStdString ss to include the terminal slash.
                TStdString ss;
                if (s[s.length()-1] == '/') {
                    ss = s;
                } else {
                    ss = s+'/';
                }

                int length_change = (int) (ss.length() - _basename_start);

                _filename.replace(0, _basename_start, ss);

                _dirname_end = ss.length() - 1;

                // An exception: if the dirname TStdString was the single slash, the
                // dirname includes that slash.
                if (ss.length() == 1) {
                    _dirname_end = 1;
                }

                _basename_start += length_change;

                if (_basename_end != TStdString::npos) {
                    _basename_end += length_change;
                    _extension_start += length_change;
                }
            }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::set_basename
    //       Access: Public
    //  Description: Replaces the basename part of the filename.  This is
    //               everything in the filename after the rightmost slash,
    //               including any extensions.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        set_basename(const TStdString &s) {
            _filename.replace(_basename_start, TStdString::npos, s);
            locate_extension();
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::set_fullpath_wo_extension
    //       Access: Public
    //  Description: Replaces the full filename--directory and basename
    //               parts--except for the extension.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        set_fullpath_wo_extension(const TStdString &s) {
            int length_change = int(s.length() - _basename_end);

            _filename.replace(0, _basename_end, s);

            if (_basename_end != TStdString::npos) {
                _basename_end += length_change;
                _extension_start += length_change;
            }
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::set_basename_wo_extension
    //       Access: Public
    //  Description: Replaces the basename part of the filename, without
    //               the file extension.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        set_basename_wo_extension(const TStdString &s) {
            int length_change = int(s.length() - (_basename_end - _basename_start));

            if (_basename_end == TStdString::npos) {
                _filename.replace(_basename_start, TStdString::npos, s);

            } else {
                _filename.replace(_basename_start, _basename_end - _basename_start, s);

                _basename_end += length_change;
                _extension_start += length_change;
            }
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::set_extension
    //       Access: Public
    //  Description: Replaces the file extension.  This is everything after
    //               the rightmost dot, if there is one, or the empty
    //               TStdString if there is not.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        set_extension(const TStdString &s) {
            if (s.empty()) {
                // Remove the extension altogether.
                if (_basename_end != TStdString::npos) {
                    _filename.replace(_basename_end, TStdString::npos, "");
                    _basename_end = TStdString::npos;
                    _extension_start = TStdString::npos;
                }

            } else if (_basename_end == TStdString::npos) {
                // Insert an extension where there was none before.
                _basename_end = _filename.length();
                _extension_start = _filename.length() + 1;
                _filename += '.' + s;

            } else {
                // Replace an existing extension.
                _filename.replace(_extension_start, TStdString::npos, s);
            }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::extract_components
    //       Access: Public
    //  Description: Extracts out the individual directory components of
    //               the path into a series of strings.  get_basename()
    //               will be the last component stored in the vector.
    //               Note that no distinction is made by this method
    //               between a leading slash and no leading slash, but you
    //               can call is_local() to differentiate the two cases.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        extract_components(vector_string &components) const {
            components.clear();

            size_t p = 0;
            if (!_filename.empty() && _filename[0] == '/') {
                // Skip the leading slash.
                p = 1;
            }
            while (p < _filename.length()) {
                size_t q = _filename.find('/', p);
                if (q == TStdString::npos) {
                    components.push_back(_filename.substr(p));
                    return;
                }
                components.push_back(_filename.substr(p, q - p));
                p = q + 1;
            }

            // A trailing slash means we have an empty get_basename().
            components.push_back(TStdString());
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::standardize
    //       Access: Public
    //  Description: Converts the filename to standard form by replacing
    //               consecutive slashes with a single slash, removing a
    //               trailing slash if present, and backing up over ../
    //               sequences within the filename where possible.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        standardize() {
            assert(!_filename.empty());
            if (_filename == ".") {
                // Don't change a single dot; this refers to the current directory.
                return;
            }

            std::vector<TStdString> components;

            // Pull off the components of the filename one at a time.
            bool global = (_filename[0] == '/');

            size_t p = 0;
            while (p < _filename.length() && _filename[p] == '/') {
                p++;
            }
            while (p < _filename.length()) {
                size_t slash = _filename.find('/', p);
                TStdString component = _filename.substr(p, slash - p);
                if (component == ".") {
                    // Ignore /./.
                } else if (component == ".." && !components.empty() &&
                    !(components.back() == "..")) {
                        // Back up.
                        components.pop_back();
                } else {
                    components.push_back(component);
                }

                p = slash;
                while (p < _filename.length() && _filename[p] == '/') {
                    p++;
                }
            }

            // Now reassemble the filename.
            TStdString result;
            if (global) {
                result = "/";
            }
            if (!components.empty()) {
                result += components[0];
                for (int i = 1; i < (int)components.size(); i++) {
                    result += "/" + components[i];
                }
            }

            (*this) = result;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::make_absolute
    //       Access: Public
    //  Description: Converts the filename to a fully-qualified pathname
    //               from the root (if it is a relative pathname), and
    //               then standardizes it (see standardize()).
    //
    //               This is sometimes a little problematic, since it may
    //               convert the file to its 'true' absolute pathname,
    //               which could be an ugly NFS-named file, irrespective
    //               of symbolic links
    //               (e.g. /.automount/dimbo/root/usr2/fit/people/drose
    //               instead of /fit/people/drose); besides being ugly,
    //               filenames like this may not be consistent across
    //               multiple different platforms.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        make_absolute() {
            make_absolute(TExecutionEnvironment::get_cwd());
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::make_absolute
    //       Access: Public
    //  Description: Converts the filename to a fully-qualified filename
    //               from the root (if it is a relative filename), and
    //               then standardizes it (see standardize()).  This
    //               flavor accepts a specific starting directory that the
    //               filename is known to be relative to.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        make_absolute(const TFile &start_directory) {
            if (is_local()) {
                (*this) = TFile(start_directory, _filename);
            }

            standardize();
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::make_canonical
    //       Access: Public
    //  Description: Converts this filename to a canonical name by
    //               replacing the directory part with the fully-qualified
    //               directory part.  This is done by changing to that
    //               directory and calling getcwd().
    //
    //               This has the effect of (a) converting relative paths
    //               to absolute paths (but see make_absolute() if this is
    //               the only effect you want), and (b) always resolving a
    //               given directory name to the same TStdString, even if
    //               different symbolic links are traversed, and (c)
    //               changing nice symbolic-link paths like
    //               /fit/people/drose to ugly NFS automounter names like
    //               /hosts/dimbo/usr2/fit/people/drose.  This can be
    //               troubling, but sometimes this is exactly what you
    //               want, particularly if you're about to call
    //               make_relative_to() between two filenames.
    //
    //               The return value is true if successful, or false on
    //               failure (usually because the directory name does not
    //               exist or cannot be chdir'ed into).
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        make_canonical() {
            if (empty()) {
                // An empty filename is a special case.  This doesn't name
                // anything.
                return false;
            }

            if (get_fullpath() == "/") {
                // The root directory is a special case.
                return true;
            }

            // Temporarily save the current working directory.
            TFile cwd = TExecutionEnvironment::get_cwd();
            return r_make_canonical(cwd);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::to_os_specific
    //       Access: Public
    //  Description: Converts the filename from our generic Unix-like
    //               convention (forward slashes starting with the root at
    //               '/') to the corresponding filename in the local
    //               operating system (slashes in the appropriate
    //               direction, starting with the root at C:\, for
    //               instance).  Returns the TStdString representing the
    //               converted filename, but does not change the TFile
    //               itself.
    //
    //               See also from_os_specific().
    ////////////////////////////////////////////////////////////////////
    TStdString TFile::
        to_os_specific() const {
            if (empty()) {
                return TStdString();
            }
            TFile standard(*this);
            standard.standardize();

#ifdef TUBRAS_PLATFORM_WINDOWS
            switch (get_type()) {
  case T_dso:
      return convert_dso_pathname(standard.get_fullpath(), true);
  case T_executable:
      return convert_executable_pathname(standard.get_fullpath(), true);
  default:
      return convert_pathname(standard.get_fullpath(), true);
            }
#else // WIN32
            return standard;
#endif // WIN32
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::to_os_generic
    //       Access: Public
    //  Description: This is similar to to_os_specific(), but it is
    //               designed to generate a filename that can be
    //               understood on as many platforms as possible.  Since
    //               Windows can usually understand a
    //               forward-slash-delimited filename, this means it does
    //               the same thing as to_os_specific(), but it uses
    //               forward slashes instead of backslashes.
    //
    //               This method has a pretty limited use; it should
    //               generally be used for writing file references to a
    //               file that might be read on any operating system.
    ////////////////////////////////////////////////////////////////////
    TStdString TFile::
        to_os_generic() const {
            if (empty()) {
                return TStdString();
            }
            TFile standard(*this);
            standard.standardize();

#ifdef TUBRAS_PLATFORM_WINDOWS
            switch (get_type()) {
  case T_dso:
      return convert_dso_pathname(standard.get_fullpath(), false);
  case T_executable:
      return convert_executable_pathname(standard.get_fullpath(), false);
  default:
      return convert_pathname(standard.get_fullpath(), false);
            }
#else // WIN32
            return standard;
#endif // WIN32
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::exists
    //       Access: Public
    //  Description: Returns true if the filename exists on the disk,
    //               false otherwise.  If the type is indicated to be
    //               executable, this also tests that the file has execute
    //               permission.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        exists() const {
            TStdString os_specific = to_os_specific();

#ifdef TUBRAS_PLATFORM_WINDOWS
            bool exists = false;

            struct _stat buf;
            DWORD results = _stat(os_specific.c_str(),&buf);
            if (results == 0) {
                exists = true;
            }

#else  // WIN32
            struct stat this_buf;
            bool exists = false;

            if (stat(os_specific.c_str(), &this_buf) == 0) {
                exists = true;
            }
#endif

            return exists;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::is_regular_file
    //       Access: Public
    //  Description: Returns true if the filename exists and is the
    //               name of a regular file (i.e. not a directory or
    //               device), false otherwise.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        is_regular_file() const {
            TStdString os_specific = to_os_specific();

#ifdef TUBRAS_PLATFORM_WINDOWS
            bool isreg = false;


            struct _stat buf;
            DWORD results = _stat(os_specific.c_str(),&buf);
            if (results == 0) {
                isreg = (buf.st_mode & _S_IFREG) ? true : false;
            }

#else  // WIN32
            struct stat this_buf;
            bool isreg = false;

            if (stat(os_specific.c_str(), &this_buf) == 0) {
                isreg = S_ISREG(this_buf.st_mode);
            }
#endif

            return isreg;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::is_directory
    //       Access: Public
    //  Description: Returns true if the filename exists and is a
    //               directory name, false otherwise.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        is_directory() const {
            TStdString os_specific = to_os_specific();

#ifdef TUBRAS_PLATFORM_WINDOWS
            bool isdir = false;


            struct _stat buf;
            DWORD results = _stat(os_specific.c_str(),&buf);
            if (results == 0) {
                isdir = (buf.st_mode & _S_IFDIR) ? true : false;
            }
#else  // WIN32
            struct stat this_buf;
            bool isdir = false;

            if (stat(os_specific.c_str(), &this_buf) == 0) {
                isdir = S_ISDIR(this_buf.st_mode);
            }
#endif

            return isdir;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::is_executable
    //       Access: Public
    //  Description: Returns true if the filename exists and is
    //               executable
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        is_executable() const {
#ifdef TUBRAS_PLATFORM_WINDOWS
            // no access() in windows, but to our advantage executables can only
            // end in .exe or .com
            TStdString extension = get_extension();
            if (extension == "exe" || extension == "com") {
                return exists();
            }

#else /* WIN32 */
            TStdString os_specific = to_os_specific();
            if (access(os_specific.c_str(), X_OK) == 0) {
                return true;
            }
#endif /* WIN32 */

            return false;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::compare_timestamps
    //       Access: Public
    //  Description: Returns a number less than zero if the file named by
    //               this object is older than the given file, zero if
    //               they have the same timestamp, or greater than zero if
    //               this one is newer.
    //
    //               If this_missing_is_old is true, it indicates that a
    //               missing file will be treated as if it were older than
    //               any other file; otherwise, a missing file will be
    //               treated as if it were newer than any other file.
    //               Similarly for other_missing_is_old.
    ////////////////////////////////////////////////////////////////////
    int TFile::
        compare_timestamps(const TFile &other,
        bool this_missing_is_old,
        bool other_missing_is_old) const {
            TStdString os_specific = to_os_specific();
            TStdString other_os_specific = other.to_os_specific();

#ifdef TUBRAS_PLATFORM_WINDOWS
            struct _stat this_buf;
            bool this_exists = false;

            if (_stat(os_specific.c_str(), &this_buf) == 0) {
                this_exists = true;
            }

            struct _stat other_buf;
            bool other_exists = false;

            if (_stat(other_os_specific.c_str(), &other_buf) == 0) {
                other_exists = true;
            }
#else  // WIN32
            struct stat this_buf;
            bool this_exists = false;

            if (stat(os_specific.c_str(), &this_buf) == 0) {
                this_exists = true;
            }

            struct stat other_buf;
            bool other_exists = false;

            if (stat(other_os_specific.c_str(), &other_buf) == 0) {
                other_exists = true;
            }
#endif

            if (this_exists && other_exists) {
                // Both files exist, return the honest time comparison.
                return (int)this_buf.st_mtime - (int)other_buf.st_mtime;

            } else if (!this_exists && !other_exists) {
                // Neither file exists.
                if (this_missing_is_old == other_missing_is_old) {
                    // Both files are either "very old" or "very new".
                    return 0;
                }
                if (this_missing_is_old) {
                    // This file is "very old", the other is "very new".
                    return -1;
                } else {
                    // This file is "very new", the other is "very old".
                    return 1;
                }

            } else if (!this_exists) {
                // This file doesn't, the other one does.
                return this_missing_is_old ? -1 : 1;

            } else { // !other_exists
                assert(!other_exists);

                // This file exists, the other one doesn't.
                return other_missing_is_old ? 1 : -1;
            }
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::resolve_filename
    //       Access: Public
    //  Description: Searches the given search path for the filename.  If
    //               it is found, updates the filename to the full
    //               pathname found and returns true; otherwise, returns
    //               false.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        resolve_filename(const TSearchPath &searchpath,
        const TStdString &default_extension) {
            TStdString found;

            if (is_local()) {
                found = searchpath.find_file(get_fullpath());

                if (found.empty()) {
                    // We didn't find it with the given extension; can we try the
                    // default extension?
                    if (get_extension().empty() && !default_extension.empty()) {
                        TFile try_ext = *this;
                        try_ext.set_extension(default_extension);
                        found = searchpath.find_file(try_ext.get_fullpath());
                    }
                }

            } else {
                if (exists()) {
                    // The full pathname exists.  Return true.
                    return true;

                } else {
                    // The full pathname doesn't exist with the given extension;
                    // does it exist with the default extension?
                    if (get_extension().empty() && !default_extension.empty()) {
                        TFile try_ext = *this;
                        try_ext.set_extension(default_extension);
                        if (try_ext.exists()) {
                            found = try_ext;
                        }
                    }
                }
            }

            if (!found.empty()) {
                (*this) = found;
                return true;
            }

            return false;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::make_relative_to
    //       Access: Public
    //  Description: Adjusts this filename, which must be a
    //               fully-specified pathname beginning with a slash, to
    //               make it a relative filename, relative to the
    //               fully-specified directory indicated (which must also
    //               begin with, and may or may not end with, a slash--a
    //               terminating slash is ignored).
    //
    //               This only performs a TStdString comparsion, so it may be
    //               wise to call make_canonical() on both filenames
    //               before calling make_relative_to().
    //
    //               If allow_backups is false, the filename will only be
    //               adjusted to be made relative if it is already
    //               somewhere within or below the indicated directory.
    //               If allow_backups is true, it will be adjusted in all
    //               cases, even if this requires putting a series of ../
    //               characters before the filename--unless it would have
    //               to back all the way up to the root.
    //
    //               Returns true if the file was adjusted, false if it
    //               was not.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        make_relative_to(TFile directory, bool allow_backups) {
            if (_filename.empty() || directory.empty() ||
                _filename[0] != '/' || directory[0] != '/') {
                    return false;
            }

            standardize();
            directory.standardize();

            if (directory == "/") {
                // Don't be silly.
                return false;
            }

            TStdString rel_to_file = directory.get_fullpath() + "/.";

            size_t common = get_common_prefix(rel_to_file);
            if (common < 2) {
                // Oh, never mind.
                return false;
            }

            TStdString result;
            int slashes = count_slashes(rel_to_file.substr(common));
            if (slashes > 0 && !allow_backups) {
                // Too bad; the file's not under the indicated directory.
                return false;
            }

            for (int i = 0; i < slashes; i++) {
                result += "../";
            }
            result += _filename.substr(common);
            (*this) = result;

            return true;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::find_on_searchpath
    //       Access: Public
    //  Description: Performs the reverse of the resolve_filename()
    //               operation: assuming that the current filename is
    //               fully-specified pathname (i.e. beginning with '/'),
    //               look on the indicated search path for a directory
    //               under which the file can be found.  When found,
    //               adjust the TFile to be relative to the indicated
    //               directory name.
    //
    //               Returns the index of the directory on the searchpath
    //               at which the file was found, or -1 if it was not
    //               found.
    ////////////////////////////////////////////////////////////////////
    int TFile::
        find_on_searchpath(const TSearchPath &searchpath) {
            if (_filename.empty() || _filename[0] != '/') {
                return -1;
            }

            int num_directories = searchpath.get_num_directories();
            for (int i = 0; i < num_directories; i++) {
                if (make_relative_to(searchpath.get_directory(i), false)) {
                    return i;
                }
            }

            return -1;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::scan_directory
    //       Access: Public
    //  Description: Attempts to open the named filename as if it were a
    //               directory and looks for the non-hidden files within
    //               the directory.  Fills the given vector up with the
    //               sorted list of filenames that are local to this
    //               directory.
    //
    //               It is the user's responsibility to ensure that the
    //               contents vector is empty before making this call;
    //               otherwise, the new files will be appended to it.
    //
    //               Returns true on success, false if the directory could
    //               not be read for some reason.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        scan_directory(vector_string &contents) const {
#ifdef TUBRAS_PLATFORM_WINDOWS
            // Use Windows' FindFirstFile() / FindNextFile() to walk through the
            // list of files in a directory.
            size_t orig_size = contents.size();
            TStdString match;
            if (empty()) {
                match = "*.*";
            } else {
                match = to_os_specific() + "\\*.*";
            }
            WIN32_FIND_DATAA find_data;

            HANDLE handle = FindFirstFileA(match.c_str(), &find_data);
            if (handle == INVALID_HANDLE_VALUE) {
                if (GetLastError() == ERROR_NO_MORE_FILES) {
                    // No matching files is not an error.
                    return true;
                }
                return false;
            }

            do {
                TStdString filename = find_data.cFileName;
                if (filename != "." && filename != "..") {
                    contents.push_back(filename);
                }
            } while (FindNextFileA(handle, &find_data));

            bool scan_ok = (GetLastError() == ERROR_NO_MORE_FILES);
            FindClose(handle);

            contents.sort();
            return scan_ok;

#elif defined(HAVE_DIRENT_H)
            // Use Posix's opendir() / readir() to walk through the list of
            // files in a directory.

            TStdString dirname;
            if (empty()) {
                dirname = ".";
            } else {
                dirname = _filename;
            }
            DIR *root = opendir(dirname.c_str());
            if (root == (DIR *)NULL) {
                perror(dirname.c_str());
                return false;
            }

            struct dirent *d;
            d = readdir(root);
            while (d != (struct dirent *)NULL) {
                if (d->d_name[0] != '.') {
                    contents.push_back(d->d_name);
                }
                d = readdir(root);
            }

            // It turns out to be a mistake to check the value of errno after
            // calling readdir(), since it might have been set to non-zero
            // during some internal operation of readdir(), even though there
            // wasn't really a problem with scanning the directory itself.
            /*
            if (errno != 0 && errno != ENOENT && errno != ENOTDIR) {
            cerr << "Error occurred while scanning directory " << dirname << "\n";
            perror(dirname.c_str());
            closedir(root);
            return false;
            }
            */
            closedir(root);
            contents.sort();
            //sort(contents.begin() + orig_size, contents.end());
            return true;

#elif defined(HAVE_GLOB_H)
            // It's hard to imagine a system that provides glob.h but does not
            // provide openddir() .. readdir(), but this code is leftover from a
            // time when there was an undetected bug in the above readdir()
            // loop, and it works, so we might as well keep it around for now.
            TStdString dirname;
            if (empty()) {
                dirname = "*";
            } else if (_filename[_filename.length() - 1] == '/') {
                dirname = _filename + "*";
            } else {
                dirname = _filename + "/*";   /* comment to fix emacs syntax hilight */
            }

            glob_t globbuf;

            int r = glob(dirname.c_str(), GLOB_ERR, NULL, &globbuf);

            if (r != 0) {
                // Some error processing the match TStdString.  If our version of
                // glob.h defines GLOB_NOMATCH, then we can differentiate an empty
                // return result from some other kind of error.
#ifdef GLOB_NOMATCH
                if (r != GLOB_NOMATCH) {
                    perror(dirname.c_str());
                    return false;
                }
#endif

                // Otherwise, all errors mean the same thing: no matches, but
                // otherwise no problem.
                return true;
            }

            size_t offset = dirname.size() - 1;

            for (int i = 0; globbuf.gl_pathv[i] != NULL; i++) {
                contents.push_back(globbuf.gl_pathv[i] + offset);
            }
            globfree(&globbuf);

            return true;

#else
            // Don't know how to scan directories!
            return false;
#endif
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::open_read
    //       Access: Public
    //  Description: Opens the indicated ifstream for reading the file, if
    //               possible.  Returns true if successful, false
    //               otherwise.  This requires the setting of the
    //               set_text()/set_binary() flags to open the file
    //               appropriately as indicated; it is an error to call
    //               open_read() without first calling one of set_text()
    //               or set_binary().
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        open_read(std::ifstream &stream) const {
            assert(is_text() || is_binary());

            ios_openmode open_mode = std::ios::in;

#ifdef HAVE_IOS_BINARY
            // For some reason, some systems (like Irix) don't define
            // ios::binary.
            if (!is_text()) {
                open_mode |= ios::binary;
            }
#endif

            TStdString os_specific = to_os_specific();
            stream.clear();
            stream.open(os_specific.c_str(), open_mode);
            return (!stream.fail());
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::open_write
    //       Access: Public
    //  Description: Opens the indicated ifstream for writing the file, if
    //               possible.  Returns true if successful, false
    //               otherwise.  This requires the setting of the
    //               set_text()/set_binary() flags to open the file
    //               appropriately as indicated; it is an error to call
    //               open_read() without first calling one of set_text()
    //               or set_binary().
    //
    //               If truncate is true, the file is truncated to zero
    //               length upon opening it, if it already exists.
    //               Otherwise, the file is kept at its original length.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        open_write(std::ofstream &stream, bool truncate) const {
            assert(is_text() || is_binary());

            ios_openmode open_mode = std::ios::out;

            if (truncate) {
                open_mode |= std::ios::trunc;

            } else {
                // Some systems insist on having ios::in set to prevent the file
                // from being truncated when we open it.  Makes ios::trunc kind of
                // pointless, doesn't it?  On the other hand, setting ios::in also
                // seems to imply ios::nocreate (!), so we should only set this if
                // the file already exists.
                if (exists()) {
                    open_mode |= std::ios::in;
                }
            }

#ifdef HAVE_IOS_BINARY
            // For some reason, some systems (like Irix) don't define
            // ios::binary.
            if (!is_text()) {
                open_mode |= ios::binary;
            }
#endif

            stream.clear();
            TStdString os_specific = to_os_specific();
#ifdef HAVE_OPEN_MASK
            stream.open(os_specific.c_str(), open_mode, 0666);
#else
            stream.open(os_specific.c_str(), open_mode);
#endif

            return (!stream.fail());
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::open_append
    //       Access: Public
    //  Description: Opens the indicated ifstream for writing the file, if
    //               possible.  Returns true if successful, false
    //               otherwise.  This requires the setting of the
    //               set_text()/set_binary() flags to open the file
    //               appropriately as indicated; it is an error to call
    //               open_read() without first calling one of set_text()
    //               or set_binary().
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        open_append(std::ofstream &stream) const {
            assert(is_text() || is_binary());

            ios_openmode open_mode = std::ios::app;

#ifdef HAVE_IOS_BINARY
            // For some reason, some systems (like Irix) don't define
            // ios::binary.
            if (!is_text()) {
                open_mode |= ios::binary;
            }
#endif

            stream.clear();
            TStdString os_specific = to_os_specific();
#ifdef HAVE_OPEN_MASK
            stream.open(os_specific.c_str(), open_mode, 0666);
#else
            stream.open(os_specific.c_str(), open_mode);
#endif

            return (!stream.fail());
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::open_read_write
    //       Access: Public
    //  Description: Opens the indicated fstream for read/write access to
    //               the file, if possible.  Returns true if successful,
    //               false otherwise.  This requires the setting of the
    //               set_text()/set_binary() flags to open the file
    //               appropriately as indicated; it is an error to call
    //               open_read_write() without first calling one of
    //               set_text() or set_binary().
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        open_read_write(std::fstream &stream) const {
            assert(is_text() || is_binary());

            ios_openmode open_mode = std::ios::out | std::ios::in;

            // Since ios::in also seems to imply ios::nocreate (!), we must
            // guarantee the file already exists before we try to open it.
            if (!exists()) {
                touch();
            }

#ifdef HAVE_IOS_BINARY
            // For some reason, some systems (like Irix) don't define
            // ios::binary.
            if (!is_text()) {
                open_mode |= ios::binary;
            }
#endif

            stream.clear();
            TStdString os_specific = to_os_specific();
#ifdef HAVE_OPEN_MASK
            stream.open(os_specific.c_str(), open_mode, 0666);
#else
            stream.open(os_specific.c_str(), open_mode);
#endif

            return (!stream.fail());
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::touch
    //       Access: Public
    //  Description: Updates the modification time of the file to the
    //               current time.  If the file does not already exist, it
    //               will be created.  Returns true if successful, false
    //               if there is an error.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        touch() const {
#ifdef TUBRAS_PLATFORM_WINDOWS
            // In Windows, we have to use the Windows API to do this reliably.

            // First, guarantee the file exists (and also get its handle).
            TStdString os_specific = to_os_specific();
            HANDLE fhandle;
            fhandle = CreateFileA(os_specific.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE,
                NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (fhandle == INVALID_HANDLE_VALUE) {
                return false;
            }

            // Now update the file time and date.
            SYSTEMTIME sysnow;
            FILETIME ftnow;
            GetSystemTime(&sysnow);
            if (!SystemTimeToFileTime(&sysnow, &ftnow)) {
                CloseHandle(fhandle);
                return false;
            }

            if (!SetFileTime(fhandle, NULL, NULL, &ftnow)) {
                CloseHandle(fhandle);
                return false;
            }

            CloseHandle(fhandle);
            return true;

#elif defined(HAVE_UTIME_H)
            // Most Unix systems can do this explicitly.

            TStdString os_specific = to_os_specific();
#ifdef HAVE_CYGWIN
            // In the Cygwin case, it seems we need to be sure to use the
            // Cygwin-style name; some broken utime() implementation.  That's
            // almost the same thing as the original Panda-style name, but not
            // exactly, so we first convert the Panda name to a Windows name,
            // then convert it back to Cygwin, to ensure we get it exactly right
            // by Cygwin rules.
            {
                char result[4096] = "";
                cygwin_conv_to_posix_path(os_specific.c_str(), result);
                os_specific = result;
            }
#endif  // HAVE_CYGWIN
            int result = utime(os_specific.c_str(), NULL);
            if (result < 0) {
                if (errno == ENOENT) {
                    // So the file doesn't already exist; create it.
                    int fd = creat(os_specific.c_str(), 0666);
                    if (fd < 0) {
                        perror(os_specific.c_str());
                        return false;
                    }
                    close(fd);
                    return true;
                }
                perror(os_specific.c_str());
                return false;
            }
            return true;
#else  // WIN32, HAVE_UTIME_H
            // Other systems may not have an explicit control over the
            // modification time.  For these systems, we'll just temporarily
            // open the file in append mode, then close it again (it gets closed
            // when the ofstream goes out of scope).
            std::ofstream file;
            return open_append(file);
#endif  // WIN32, HAVE_UTIME_H
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::unlink
    //       Access: Public
    //  Description: Permanently deletes the file associated with the
    //               filename, if possible.  Returns true if successful,
    //               false if failure (for instance, because the file did
    //               not exist, or because permissions were inadequate).
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        unlink() const {
            TStdString os_specific = to_os_specific();
#ifdef TUBRAS_PLATFORM_WINDOWS
            return (::_unlink(os_specific.c_str()) == 0);
#else
            return (::unlink(os_specific.c_str()) == 0);
#endif
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::rename_to
    //       Access: Public
    //  Description: Renames the file to the indicated new filename.  If
    //               the new filename is in a different directory, this
    //               will perform a move.  Returns true if successful,
    //               false if failure.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        rename_to(const TFile &other) const {
            TStdString os_specific = to_os_specific();
            TStdString other_os_specific = other.to_os_specific();
            return (rename(os_specific.c_str(),
                other_os_specific.c_str()) == 0);
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::make_dir
    //       Access: Public
    //  Description: Creates all the directories in the path to the file
    //               specified in the filename, except for the basename
    //               itself.  This assumes that the TFile contains the
    //               name of a file, not a directory name; it ensures that
    //               the directory containing the file exists.
    //
    //               However, if the filename ends in a slash, it assumes
    //               the TFile represents the name of a directory, and
    //               creates all the paths.
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        make_dir() const {
            if (empty()) {
                return false;
            }
            TFile path = *this;
            path.standardize();
            TStdString dirname;
            if (_filename[_filename.length() - 1] == '/') {
                // The TFile ends in a slash; it represents a directory.
                dirname = path.get_fullpath();

            } else {
                // The TFile does not end in a slash; it represents a file.
                dirname = path.get_dirname();
            }

            // First, make sure everything up to the last path is known.  We
            // don't care too much if any of these fail; maybe they failed
            // because the directory was already there.
            size_t slash = dirname.find('/');
            while (slash != TStdString::npos) {
                TFile component(dirname.substr(0, slash));
                TStdString os_specific = component.to_os_specific();
#ifndef TUBRAS_PLATFORM_WINDOWS
                mkdir(os_specific.c_str(), 0777);
#else
                _mkdir(os_specific.c_str());
#endif
                slash = dirname.find('/', slash + 1);
            }

            // Now make the last one, and check the return value.
            TFile component(dirname);
            TStdString os_specific = component.to_os_specific();
#ifndef TUBRAS_PLATFORM_WINDOWS
            int result = mkdir(os_specific.c_str(), 0777);
#else
            int result = _mkdir(os_specific.c_str());
#endif

            return (result == 0);
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::locate_basename
    //       Access: Private
    //  Description: After the TStdString has been reassigned, search for the
    //               slash marking the beginning of the basename, and set
    //               _dirname_end and _basename_start correctly.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        locate_basename() {
            // Scan for the last slash, which marks the end of the directory
            // part.
            if (_filename.empty()) {
                _dirname_end = 0;
                _basename_start = 0;

            } else {

                TStdString::size_type slash = _filename.rfind(SEPARATOR);
                if (slash != TStdString::npos) {
                    _basename_start = slash + 1;
                    _dirname_end = _basename_start;

                    // One exception: in case there are multiple slashes in a row,
                    // we want to treat them as a single slash.  The directory
                    // therefore actually ends at the first of these; back up a bit.
                    while (_dirname_end > 0 && _filename[_dirname_end-1] == SEPARATOR) {
                        _dirname_end--;
                    }

                    // Another exception: if the dirname was nothing but slashes, it
                    // was the root directory, or / itself.  In this case the dirname
                    // does include the terminal slash (of course).
                    if (_dirname_end == 0) {
                        _dirname_end = 1;
                    }

                } else {
                    _dirname_end = 0;
                    _basename_start = 0;
                }
            }

            // Now:

            // _dirname_end is the last slash character, or 0 if there are no
            // slash characters.

            // _basename_start is the character after the last slash character,
            // or 0 if there are no slash characters.
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::locate_extension
    //       Access: Private
    //  Description: Once the end of the directory prefix has been found,
    //               and _dirname_end and _basename_start are set
    //               correctly, search for the dot marking the beginning
    //               of the extension, and set _basename_end and
    //               _extension_start correctly.
    ////////////////////////////////////////////////////////////////////
    void TFile::
        locate_extension() {
            // Now scan for the last dot after that slash.
            if (_filename.empty()) {
                _basename_end = TStdString::npos;
                _extension_start = TStdString::npos;

            } else {
                TStdString::size_type dot = _filename.length() - 1;

                while (dot+1 > _basename_start && _filename[dot] != '.') {
                    --dot;
                }

                if (dot+1 > _basename_start) {
                    _basename_end = dot;
                    _extension_start = dot + 1;
                } else {
                    _basename_end = TStdString::npos;
                    _extension_start = TStdString::npos;
                }
            }

            // Now:

            // _basename_end is the last dot, or npos if there is no dot.

            // _extension_start is the character after the last dot, or npos if
            // there is no dot.
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::get_common_prefix
    //       Access: Private
    //  Description: Returns the length of the longest common initial
    //               substring of this TStdString and the other one that ends
    //               in a slash.  This is the lowest directory common to
    //               both filenames.
    ////////////////////////////////////////////////////////////////////
    size_t TFile::
        get_common_prefix(const TStdString &other) const {
            size_t len = 0;

            // First, get the length of the common initial substring.
            while (len < length() && len < other.length() &&
                _filename[len] == other[len]) {
                    len++;
            }

            // Now insist that it ends in a slash.
            while (len > 0 && _filename[len-1] != '/') {
                len--;
            }

            return len;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::count_slashes
    //       Access: Private, Static
    //  Description: Returns the number of non-consecutive slashes in the
    //               indicated TStdString, not counting a terminal slash.
    ////////////////////////////////////////////////////////////////////
    int TFile::
        count_slashes(const TStdString &str) {
            int count = 0;
            TStdString::const_iterator si;
            si = str.begin();

            while (si != str.end()) {
                if (*si == '/') {
                    count++;

                    // Skip consecutive slashes.
                    ++si;
                    while (*si == '/') {
                        ++si;
                    }
                    if (si == str.end()) {
                        // Oops, that was a terminal slash.  Don't count it.
                        count--;
                    }

                } else {
                    ++si;
                }
            }

            return count;
    }


    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::r_make_canonical
    //       Access: Private
    //  Description: The recursive implementation of make_canonical().
    ////////////////////////////////////////////////////////////////////
    bool TFile::
        r_make_canonical(const TFile &cwd) {
            if (get_fullpath() == "/") {
                // If we reached the root, the whole path doesn't exist.  Report
                // failure.
                return false;
            }

            // First, try to cd to the filename directly.
            TStdString os_specific = to_os_specific();

            if (_chdir(os_specific.c_str()) >= 0) {
                // That worked, save the full path TStdString.
                (*this) = TExecutionEnvironment::get_cwd();

                // And restore the current working directory.
                TStdString osdir = cwd.to_os_specific();
                if (_chdir(osdir.c_str()) < 0) {
                    std::cerr << "Error!  Cannot change back to " << cwd << "\n";
                }
                return true;
            }

            // That didn't work; maybe it's not a directory.  Recursively go to
            // the directory above.

            TFile dir(get_dirname());

            if (dir.empty()) {
                // No dirname means the file is in this directory.
                set_dirname(cwd);
                return true;
            }

            if (!dir.r_make_canonical(cwd)) {
                return false;
            }
            set_dirname(dir);
            return true;
    }


}
