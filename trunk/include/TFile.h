//-----------------------------------------------------------------------------
// This source file is part of the Tubras game engine
//    
// For the latest info, see http://www.tubras.com
//
// Copyright (c) 2006 Tubras Software Ltd
// Also see acknowledgements in Readme.html
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place - Suite 330, Boston, MA 02111-1307, USA, or go to
// http://www.gnu.org/copyleft/lesser.txt.
//
// You may alternatively use this source under the terms of a specific version of
// the Tubras Unrestricted License provided you have obtained such a license from
// Tubras Software Ltd.
//-----------------------------------------------------------------------------

#ifndef _TFILE_H_
#define _TFILE_H_

namespace Tubras
{

    typedef std::vector<string> vector_string;
    typedef std::ios::openmode ios_openmode;
    typedef int ios_openmode;


    class TSearchPath 
    {
    public:
        class TResults 
        {
        public:
            TResults();
            TResults(const TResults &copy);
            void operator = (const TResults &copy);
            ~TResults();

            void clear();
            int get_num_files() const;
            const class TFile &get_file(int n) const;

        public:
            void add_file(const class TFile &file);

        private:
            typedef vector<class TFile> Files;
            Files _files;
        };

    public:
        TSearchPath();
        TSearchPath(const string &path, const string &delimiters = ": \n\t");
        TSearchPath(const TSearchPath &copy);
        void operator = (const TSearchPath &copy);
        ~TSearchPath();

        void clear();
        void append_directory(const class TFile &directory);
        void prepend_directory(const class TFile &directory);
        void append_path(const string &path,
            const string &delimiters = ": \n\t");
        void append_path(const TSearchPath &path);
        void prepend_path(const TSearchPath &path);

        bool is_empty() const;
        int get_num_directories() const;
        const class TFile &get_directory(int n) const;

        class TFile find_file(const class TFile &filename) const;
        int find_all_files(const class TFile &filename, TResults &results) const;

        inline static class TFile
            search_path(const class TFile &filename, const string &path,
            const string &delimiters = ": \n\t");

        void output(ostream &out, const string &separator = ":") const;
        void write(ostream &out, int indent_level = 0) const;

    private:
        typedef vector<class TFile> Directories;
        Directories _directories;
    };

    inline ostream &operator << (ostream &out, const TSearchPath &sp) {
        sp.output(out);
        return out;
    }


    class TExecutionEnvironment {
    public:
        static string get_environment_variable(const string &var);
        static string expand_string(const string &str);
        static class TFile get_cwd();
    };

    class TFile
    {
    public:

        static Ogre::Archive *findArchive(string resourceGroup,string& TFile);

        enum Type {
            // These type values must fit within the bits allocated for
            // F_type, below.
            T_general    = 0x00,
            T_dso        = 0x01,
            T_executable = 0x02,
            // Perhaps other types will be added later.
        };

    public:
        enum Flags {
            F_type            = 0x0f,
            F_binary          = 0x10,
            F_text            = 0x20,
        };

    public:
        inline TFile(const string &filename = "");
        inline TFile(const char *filename);
        inline TFile(const TFile &copy);
        TFile(const TFile &dirname, const TFile &basename);
        inline ~TFile();

        // Static constructors to explicitly create a TFile that refers
        // to a text or binary file.  This is in lieu of calling set_text()
        // or set_binary() or set_type().
        inline static TFile text_filename(const string &filename);
        inline static TFile binary_filename(const string &filename);
        inline static TFile dso_filename(const string &filename);
        inline static TFile executable_filename(const string &filename);

        static TFile from_os_specific(const string &os_specific,
            Type type = T_general);
        static TFile expand_from(const string &user_string, 
            Type type = T_general);
        static TFile temporary(const string &dirname, const string &prefix,
            Type type = T_general);

        // Assignment is via the = operator.
        inline TFile &operator = (const string &filename);
        inline TFile &operator = (const char *filename);
        inline TFile &operator = (const TFile &copy);

        // And retrieval is by any of the classic string operations.
        inline operator const string & () const;
        inline const char *c_str() const;
        inline bool empty() const;
        inline size_t length() const;
        inline char operator [] (int n) const;

        // Or, you can use any of these.
        inline string get_fullpath() const;
        inline string get_dirname() const;
        inline string get_basename() const;
        inline string get_fullpath_wo_extension() const;
        inline string get_basename_wo_extension() const;
        inline string get_extension() const;

        // You can also use any of these to reassign pieces of the TFile.
        void set_fullpath(const string &s);
        void set_dirname(const string &s);
        void set_basename(const string &s);
        void set_fullpath_wo_extension(const string &s);
        void set_basename_wo_extension(const string &s);
        void set_extension(const string &s);

        // Setting these flags appropriately is helpful when opening or
        // searching for a file; it helps the TFile resolve OS-specific
        // conventions (for instance, that dynamic library names should
        // perhaps be changed from .so to .dll).
        inline void set_binary();
        inline void set_text();
        inline bool is_binary() const;
        inline bool is_text() const;

        inline void set_type(Type type);
        inline Type get_type() const;

        void extract_components(vector_string &components) const;
        void standardize();

        // The following functions deal with the outside world.

        inline bool is_local() const;
        inline bool is_fully_qualified() const;
        void make_absolute();
        void make_absolute(const TFile &start_directory);

        bool make_canonical();

        string to_os_specific() const;
        string to_os_generic() const;

        bool exists() const;
        bool is_regular_file() const;
        bool is_directory() const;
        bool is_executable() const;
        int compare_timestamps(const TFile &other,
            bool this_missing_is_old = true,
            bool other_missing_is_old = true) const;
        bool resolve_filename(const TSearchPath &searchpath,
            const string &default_extension = string());
        bool make_relative_to(TFile directory, bool allow_backups = true);
        int find_on_searchpath(const TSearchPath &searchpath);

        bool scan_directory(vector_string &contents) const;

        bool open_read(ifstream &stream) const;
        bool open_write(ofstream &stream, bool truncate = true) const;
        bool open_append(ofstream &stream) const;
        bool open_read_write(fstream &stream) const;

        bool touch() const;

        bool unlink() const;
        bool rename_to(const TFile &other) const;

        bool make_dir() const;

        // Comparison operators are handy.
        inline bool operator == (const string &other) const;
        inline bool operator != (const string &other) const;
        inline bool operator < (const string &other) const;

        inline void output(ostream &out) const;

    private:
        void locate_basename();
        void locate_extension();
        size_t get_common_prefix(const string &other) const;
        static int count_slashes(const string &str);
        bool r_make_canonical(const TFile &cwd);

        string _filename;
        // We'll make these size_t instead of string::size_type to help out
        // cppParser.
        size_t _dirname_end;
        size_t _basename_start;
        size_t _basename_end;
        size_t _extension_start;

        int _flags;

    };

    inline ostream &operator << (ostream &out, const TFile &n) {
        n.output(out);
        return out;
    }

    ////////////////////////////////////////////////////////////////////
    //     Function: TFile::Constructor
    //       Access: Public
    //  Description:
    ////////////////////////////////////////////////////////////////////
    inline TFile::
        TFile(const string &filename) {
            (*this) = filename;
            _flags = 0;
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile::TFile(const char *filename) 
    {
        (*this) = filename;
        _flags = 0;
    }


    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile::TFile(const TFile &copy)
        : _filename(copy._filename),
        _dirname_end(copy._dirname_end),
        _basename_start(copy._basename_start),
        _basename_end(copy._basename_end),
        _extension_start(copy._extension_start),
        _flags(copy._flags)
    {
    }

    //-----------------------------------------------------------------------
    //                       t e x t F i l e n a m e
    //-----------------------------------------------------------------------
    inline TFile TFile::text_filename(const string &filename) 
    {
        TFile result(filename);
        result.set_text();
        return result;
    }

    //-----------------------------------------------------------------------
    //                     b i n a r y F i l e n a m e
    //-----------------------------------------------------------------------
    inline TFile TFile::binary_filename(const string &filename) {
        TFile result(filename);
        result.set_binary();
        return result;
    }

    //-----------------------------------------------------------------------
    //                        d s o F i l e n a m e
    //-----------------------------------------------------------------------
    inline TFile TFile::dso_filename(const string &filename) 
    {
        TFile result(filename);
        result.set_type(T_dso);
        return result;
    }

    //-----------------------------------------------------------------------
    //                  e x e c u t a b l e F i l e n a m e
    //-----------------------------------------------------------------------
    inline TFile TFile::executable_filename(const string &filename) 
    {
        TFile result(filename);
        result.set_type(T_executable);
        return result;
    }

    //-----------------------------------------------------------------------
    //                            ~ T F i l e
    //-----------------------------------------------------------------------
    inline TFile::~TFile() 
    {
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile &TFile::operator = (const string &filename) 
    {
        _filename = filename;

        locate_basename();
        locate_extension();
        return *this;
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile &TFile::operator = (const char *filename)
    {
        assert(filename != NULL);
        return (*this) = string(filename);
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile &TFile::operator = (const TFile &copy) 
    {
        _filename = copy._filename;
        _dirname_end = copy._dirname_end;
        _basename_start = copy._basename_start;
        _basename_end = copy._basename_end;
        _extension_start = copy._extension_start;
        _flags = copy._flags;
        return *this;
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline TFile::operator const string & () const 
    {
        return _filename;
    }

    //-----------------------------------------------------------------------
    //                          c _ s t r 
    //-----------------------------------------------------------------------
    inline const char *TFile::c_str() const 
    {
        return _filename.c_str();
    }

    //-----------------------------------------------------------------------
    //                          e m p t y 
    //-----------------------------------------------------------------------
    inline bool TFile::empty() const 
    {
        return _filename.empty();
    }

    //-----------------------------------------------------------------------
    //                           l e n g t h 
    //-----------------------------------------------------------------------
    inline size_t TFile::length() const 
    {
        return _filename.length();
    }

    //-----------------------------------------------------------------------
    //                          T F i l e
    //-----------------------------------------------------------------------
    inline char TFile::operator [] (int n) const 
    {
        assert(n >= 0 && n < (int)_filename.length());
        return _filename[n];
    }


    //-----------------------------------------------------------------------
    //                          g e t F u l l P a t h
    //-----------------------------------------------------------------------
    inline string TFile::get_fullpath() const 
    {
        return _filename;
    }

    //-----------------------------------------------------------------------
    //                          g e t D i r N a m e
    //-----------------------------------------------------------------------
    inline string TFile::get_dirname() const 
    {
        return _filename.substr(0, _dirname_end);
    }

    //-----------------------------------------------------------------------
    //                          g e t B a s e N a m e
    //-----------------------------------------------------------------------
    inline string TFile::get_basename() const 
    {
        return _filename.substr(_basename_start);
    }


    //-----------------------------------------------------------------------
    //                g e t F u l l P a t h W O E x t e n s i o n
    //-----------------------------------------------------------------------
    inline string TFile::get_fullpath_wo_extension() const 
    {
        return _filename.substr(0, _basename_end);
    }


    //-----------------------------------------------------------------------
    //                g e t B a s e N a m e W O E x t e n s i o n 
    //-----------------------------------------------------------------------
    inline string TFile::get_basename_wo_extension() const 
    {
        if (_basename_end == string::npos) {
            return _filename.substr(_basename_start);
        } else {
            return _filename.substr(_basename_start, _basename_end - _basename_start);
        }
    }


    //-----------------------------------------------------------------------
    //                          g e t E x t e n s i o n
    //-----------------------------------------------------------------------
    inline string TFile::get_extension() const 
    {
        if (_extension_start == string::npos) 
        {
            return string();
        } else 
        {
            return _filename.substr(_extension_start);
        }
    }

    //-----------------------------------------------------------------------
    //                          s e t B i n a r y
    //-----------------------------------------------------------------------
    inline void TFile::set_binary() 
    {
        _flags = (_flags & ~F_text) | F_binary;
    }

    //-----------------------------------------------------------------------
    //                           s e t T e x t 
    //-----------------------------------------------------------------------
    inline void TFile::set_text() 
    {
        _flags = (_flags & ~F_binary) | F_text;
    }

    //-----------------------------------------------------------------------
    //                           i s B i n a r y
    //-----------------------------------------------------------------------
    inline bool TFile::is_binary() const 
    {
        return ((_flags & F_binary) != 0);
    }

    //-----------------------------------------------------------------------
    //                             i s T e x t
    //-----------------------------------------------------------------------
    inline bool TFile::is_text() const 
    {
        return ((_flags & F_text) != 0);
    }

    //-----------------------------------------------------------------------
    //                          s e t T y p e
    //-----------------------------------------------------------------------
    inline void TFile::set_type(TFile::Type type) 
    {
        _flags = (_flags & ~F_type) | type;
        switch (type) 
        {
        case T_dso:
        case T_executable:
            set_binary();

        case T_general:
            break;
        }
    }

    //-----------------------------------------------------------------------
    //                          g e t T y p e
    //-----------------------------------------------------------------------
    inline TFile::Type TFile::get_type() const 
    {
        return (Type)(_flags & (int)F_type);
    }

    //-----------------------------------------------------------------------
    //                           i s L o c a l
    //-----------------------------------------------------------------------
    inline bool TFile::is_local() const 
    {
        return _filename.empty() || _filename[0] != '/';
    }

    //-----------------------------------------------------------------------
    //                       i s F u l l y Q u a l i f i e d
    //-----------------------------------------------------------------------
    inline bool TFile::is_fully_qualified() const 
    {
        return
            (_filename.size() > 2 && _filename[0] == '.' && _filename[1] == '/') ||
            (!_filename.empty() && _filename[0] == '/');
    }

    //-----------------------------------------------------------------------
    //                                = =
    //-----------------------------------------------------------------------
    inline bool TFile::operator == (const string &other) const 
    {
        return (*(string *)this) == other;
    }

    //-----------------------------------------------------------------------
    //                                ! =
    //-----------------------------------------------------------------------
    inline bool TFile::operator != (const string &other) const 
    {
        return (*(string *)this) != other;
    }

    //-----------------------------------------------------------------------
    //                                <
    //-----------------------------------------------------------------------
    inline bool TFile::operator < (const string &other) const 
    {
        return (*(string *)this) < other;
    }


    //-----------------------------------------------------------------------
    //                            o u t p u t
    //-----------------------------------------------------------------------
    inline void TFile::output(ostream &out) const 
    {
        out << _filename;
    }

    string downcase(const string &params);

}

#endif